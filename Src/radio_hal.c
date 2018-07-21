#include "main.h"
#include "stm32f4xx_hal.h"
#include "radio_config.h"
#include "radio_hal.h"
#include "si446x_cmd.h"
#include "string.h"

extern SPI_HandleTypeDef hspi2;

void radio_hal_AssertShutdown(void)
{
	HAL_GPIO_WritePin(nRF_SDN_GPIO_Port,nRF_SDN_Pin,GPIO_PIN_SET);
}

void radio_hal_DeassertShutdown(void)
{
	HAL_GPIO_WritePin(nRF_SDN_GPIO_Port,nRF_SDN_Pin,GPIO_PIN_RESET);
}

void radio_hal_ClearNsel(void)
{
	HAL_GPIO_WritePin(nSIP2_CS_GPIO_Port,nSIP2_CS_Pin,GPIO_PIN_RESET);			// CS LOW
}

void radio_hal_SetNsel(void)
{
	HAL_GPIO_WritePin(nSIP2_CS_GPIO_Port,nSIP2_CS_Pin,GPIO_PIN_SET);			// CS LOW
}

BIT radio_hal_NirqLevel(void)
{
  return HAL_GPIO_ReadPin(RF_IRQ_GPIO_Port,RF_IRQ_Pin);
}

void radio_hal_SpiWriteByte(U8 byteToWrite)
{
  if (HAL_SPI_Transmit(&hspi2,&byteToWrite,1,10) != HAL_OK)
	{
		Error_Handler();
	}
}

U8 radio_hal_SpiReadByte(void)
{
	U8 rx_dat;
	if (HAL_SPI_Receive(&hspi2,&rx_dat,1,10) != HAL_OK)
	{
		Error_Handler();
	}
	return rx_dat;
}

void radio_hal_SpiWriteData(U8 byteCount, U8* pData)
{
  if (HAL_SPI_Transmit(&hspi2,pData,byteCount,10) != HAL_OK)
	{
		Error_Handler();
	}
}

void radio_hal_SpiReadData(U8 byteCount, U8* pData)
{
	if (HAL_SPI_Receive(&hspi2,pData,byteCount,10) != HAL_OK)
	{
		Error_Handler();
	}
}

#ifdef RADIO_DRIVER_EXTENDED_SUPPORT
GPIO_PinState radio_hal_Gpio0Level(void)
{
  GPIO_PinState retVal = GPIO_PIN_RESET;

  return retVal;
}

GPIO_PinState radio_hal_Gpio1Level(void)
{
  GPIO_PinState retVal = GPIO_PIN_RESET;

	retVal = HAL_GPIO_ReadPin(SI_GPIO1_GPIO_Port,SI_GPIO1_Pin);
  return retVal;
}

GPIO_PinState radio_hal_Gpio2Level(void)
{
  GPIO_PinState retVal = GPIO_PIN_RESET;

  return retVal;
}

GPIO_PinState radio_hal_Gpio3Level(void)
{
  GPIO_PinState retVal = GPIO_PIN_RESET;

  return retVal;
}
#endif
