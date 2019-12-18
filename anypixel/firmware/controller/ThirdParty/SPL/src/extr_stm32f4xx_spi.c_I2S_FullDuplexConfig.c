#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_7__ {scalar_t__ I2S_Mode; int I2S_Standard; int I2S_DataFormat; scalar_t__ I2S_CPOL; } ;
struct TYPE_6__ {int I2SCFGR; int I2SPR; } ;
typedef  TYPE_1__ SPI_TypeDef ;
typedef  TYPE_2__ I2S_InitTypeDef ;

/* Variables and functions */
 int I2SCFGR_CLEAR_MASK ; 
 scalar_t__ I2S_Mode_MasterRx ; 
 scalar_t__ I2S_Mode_MasterTx ; 
 scalar_t__ I2S_Mode_SlaveRx ; 
 scalar_t__ I2S_Mode_SlaveTx ; 
 int /*<<< orphan*/  IS_I2S_CPOL (scalar_t__) ; 
 int /*<<< orphan*/  IS_I2S_DATA_FORMAT (int) ; 
 int /*<<< orphan*/  IS_I2S_EXT_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_I2S_MODE (scalar_t__) ; 
 int /*<<< orphan*/  IS_I2S_STANDARD (int) ; 
 scalar_t__ SPI_I2SCFGR_I2SMOD ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void I2S_FullDuplexConfig(SPI_TypeDef* I2Sxext, I2S_InitTypeDef* I2S_InitStruct)
{
  uint16_t tmpreg = 0, tmp = 0;
  
  /* Check the I2S parameters */
  assert_param(IS_I2S_EXT_PERIPH(I2Sxext));
  assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
  assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
  assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
  assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));  

/*----------------------- SPIx I2SCFGR & I2SPR Configuration -----------------*/
  /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
  I2Sxext->I2SCFGR &= I2SCFGR_CLEAR_MASK; 
  I2Sxext->I2SPR = 0x0002;
  
  /* Get the I2SCFGR register value */
  tmpreg = I2Sxext->I2SCFGR;
  
  /* Get the mode to be configured for the extended I2S */
  if ((I2S_InitStruct->I2S_Mode == I2S_Mode_MasterTx) || (I2S_InitStruct->I2S_Mode == I2S_Mode_SlaveTx))
  {
    tmp = I2S_Mode_SlaveRx;
  }
  else
  {
    if ((I2S_InitStruct->I2S_Mode == I2S_Mode_MasterRx) || (I2S_InitStruct->I2S_Mode == I2S_Mode_SlaveRx))
    {
      tmp = I2S_Mode_SlaveTx;
    }
  }

 
  /* Configure the I2S with the SPI_InitStruct values */
  tmpreg |= (uint16_t)((uint16_t)SPI_I2SCFGR_I2SMOD | (uint16_t)(tmp | \
                  (uint16_t)(I2S_InitStruct->I2S_Standard | (uint16_t)(I2S_InitStruct->I2S_DataFormat | \
                  (uint16_t)I2S_InitStruct->I2S_CPOL))));
 
  /* Write to SPIx I2SCFGR */  
  I2Sxext->I2SCFGR = tmpreg;
}