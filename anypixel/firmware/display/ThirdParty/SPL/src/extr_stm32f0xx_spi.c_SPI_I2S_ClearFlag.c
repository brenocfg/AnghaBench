#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ SR; } ;
typedef  TYPE_1__ SPI_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SPI_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_SPI_CLEAR_FLAG (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CLEAR_FLAG(SPI_I2S_FLAG));

  /* Clear the selected SPI CRC Error (CRCERR) flag */
  SPIx->SR = (uint16_t)~SPI_I2S_FLAG;
}