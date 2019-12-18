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
struct TYPE_4__ {scalar_t__ CR2; } ;
typedef  TYPE_1__ SPI_TypeDef ;
typedef  scalar_t__ FunctionalState ;

/* Variables and functions */
 scalar_t__ DISABLE ; 
 int /*<<< orphan*/  IS_FUNCTIONAL_STATE (scalar_t__) ; 
 int /*<<< orphan*/  IS_SPI_ALL_PERIPH (TYPE_1__*) ; 
 scalar_t__ SPI_CR2_SSOE ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected SPI SS output */
    SPIx->CR2 |= (uint16_t)SPI_CR2_SSOE;
  }
  else
  {
    /* Disable the selected SPI SS output */
    SPIx->CR2 &= (uint16_t)~((uint16_t)SPI_CR2_SSOE);
  }
}