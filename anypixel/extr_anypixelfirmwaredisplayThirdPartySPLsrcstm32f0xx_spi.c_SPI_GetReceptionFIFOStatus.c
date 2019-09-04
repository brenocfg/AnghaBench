#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int SR; } ;
typedef  TYPE_1__ SPI_TypeDef ;

/* Variables and functions */
 int SPI_SR_FRLVL ; 

uint16_t SPI_GetReceptionFIFOStatus(SPI_TypeDef* SPIx)
{
  /* Get the SPIx Reception FIFO level bits */
  return (uint16_t)((SPIx->SR & SPI_SR_FRLVL));
}