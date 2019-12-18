#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_10__ {int I2S_Mode; int I2S_Standard; int I2S_DataFormat; scalar_t__ I2S_MCLKOutput; int I2S_AudioFreq; scalar_t__ I2S_CPOL; } ;
struct TYPE_9__ {int SYSCLK_Frequency; } ;
struct TYPE_8__ {int I2SCFGR; int I2SPR; } ;
typedef  TYPE_1__ SPI_TypeDef ;
typedef  TYPE_2__ RCC_ClocksTypeDef ;
typedef  TYPE_3__ I2S_InitTypeDef ;

/* Variables and functions */
 int I2SCFGR_CLEAR_Mask ; 
 int I2S_AudioFreq_Default ; 
 int I2S_DataFormat_16b ; 
 scalar_t__ I2S_MCLKOutput_Enable ; 
 int /*<<< orphan*/  IS_I2S_AUDIO_FREQ (int) ; 
 int /*<<< orphan*/  IS_I2S_CPOL (scalar_t__) ; 
 int /*<<< orphan*/  IS_I2S_DATA_FORMAT (int) ; 
 int /*<<< orphan*/  IS_I2S_MCLK_OUTPUT (scalar_t__) ; 
 int /*<<< orphan*/  IS_I2S_MODE (int) ; 
 int /*<<< orphan*/  IS_I2S_STANDARD (int) ; 
 int /*<<< orphan*/  IS_SPI_1_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  RCC_GetClocksFreq (TYPE_2__*) ; 
 int SPI_I2SCFGR_I2SMOD ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct)
{
  uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
  uint32_t tmp = 0;
  RCC_ClocksTypeDef RCC_Clocks;
  uint32_t sourceclock = 0;

  /* Check the I2S parameters */
  assert_param(IS_SPI_1_PERIPH(SPIx));
  assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
  assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
  assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
  assert_param(IS_I2S_MCLK_OUTPUT(I2S_InitStruct->I2S_MCLKOutput));
  assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->I2S_AudioFreq));
  assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));  

/*----------------------- SPIx I2SCFGR & I2SPR Configuration -----------------*/
  /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
  SPIx->I2SCFGR &= I2SCFGR_CLEAR_Mask; 
  SPIx->I2SPR = 0x0002;

  /* Get the I2SCFGR register value */
  tmpreg = SPIx->I2SCFGR;

  /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
  if(I2S_InitStruct->I2S_AudioFreq == I2S_AudioFreq_Default)
  {
    i2sodd = (uint16_t)0;
    i2sdiv = (uint16_t)2;   
  }
  /* If the requested audio frequency is not the default, compute the prescaler */
  else
  {
    /* Check the frame length (For the Prescaler computing) */
    if(I2S_InitStruct->I2S_DataFormat == I2S_DataFormat_16b)
    {
      /* Packet length is 16 bits */
      packetlength = 1;
    }
    else
    {
      /* Packet length is 32 bits */
      packetlength = 2;
    }

    /* I2S Clock source is System clock: Get System Clock frequency */
    RCC_GetClocksFreq(&RCC_Clocks);      

    /* Get the source clock value: based on System Clock value */
    sourceclock = RCC_Clocks.SYSCLK_Frequency;    

    /* Compute the Real divider depending on the MCLK output state with a floating point */
    if(I2S_InitStruct->I2S_MCLKOutput == I2S_MCLKOutput_Enable)
    {
      /* MCLK output is enabled */
      tmp = (uint16_t)(((((sourceclock / 256) * 10) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    else
    {
      /* MCLK output is disabled */
      tmp = (uint16_t)(((((sourceclock / (32 * packetlength)) *10 ) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    
    /* Remove the floating point */
    tmp = tmp / 10;

    /* Check the parity of the divider */
    i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);

    /* Compute the i2sdiv prescaler */
    i2sdiv = (uint16_t)((tmp - i2sodd) / 2);

    /* Get the Mask for the Odd bit (SPI_I2SPR[8]) register */
    i2sodd = (uint16_t) (i2sodd << 8);
  }

  /* Test if the divider is 1 or 0 or greater than 0xFF */
  if ((i2sdiv < 2) || (i2sdiv > 0xFF))
  {
    /* Set the default values */
    i2sdiv = 2;
    i2sodd = 0;
  }

  /* Write to SPIx I2SPR register the computed value */
  SPIx->I2SPR = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitStruct->I2S_MCLKOutput));

  /* Configure the I2S with the SPI_InitStruct values */
  tmpreg |= (uint16_t)(SPI_I2SCFGR_I2SMOD | (uint16_t)(I2S_InitStruct->I2S_Mode | \
                  (uint16_t)(I2S_InitStruct->I2S_Standard | (uint16_t)(I2S_InitStruct->I2S_DataFormat | \
                  (uint16_t)I2S_InitStruct->I2S_CPOL))));

  /* Write to SPIx I2SCFGR */
  SPIx->I2SCFGR = tmpreg;
}