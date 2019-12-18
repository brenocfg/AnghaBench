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
struct TYPE_4__ {scalar_t__ CR1; } ;
typedef  TYPE_1__ SPI_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SPI_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_SPI_CRC_LENGTH (scalar_t__) ; 
 scalar_t__ SPI_CR1_CRCL ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void SPI_CRCLengthConfig(SPI_TypeDef* SPIx, uint16_t SPI_CRCLength)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CRC_LENGTH(SPI_CRCLength));

  /* Clear CRCL bit */
  SPIx->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_CRCL);

  /* Set new CRCL bit value */
  SPIx->CR1 |= SPI_CRCLength;
}