#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SPI_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  IS_SPI_ALL_PERIPH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCC_APB1PeriphResetCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB1Periph_SPI2 ; 
 int /*<<< orphan*/  RCC_APB1Periph_SPI3 ; 
 int /*<<< orphan*/  RCC_APB2PeriphResetCmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_APB2Periph_SPI1 ; 
 int /*<<< orphan*/ * SPI1 ; 
 int /*<<< orphan*/ * SPI2 ; 
 int /*<<< orphan*/ * SPI3 ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void SPI_I2S_DeInit(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  if (SPIx == SPI1)
  {
    /* Enable SPI1 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
    /* Release SPI1 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
  }
  else if (SPIx == SPI2)
  {
    /* Enable SPI2 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
    /* Release SPI2 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);
    }
  else
  {
    if (SPIx == SPI3)
    {
      /* Enable SPI3 reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
      /* Release SPI3 from reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);
    }
  }
}