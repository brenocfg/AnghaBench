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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int FCR; } ;
typedef  TYPE_1__ DMA_Stream_TypeDef ;

/* Variables and functions */
 int DMA_SxFCR_FS ; 
 int /*<<< orphan*/  IS_DMA_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

uint32_t DMA_GetFIFOStatus(DMA_Stream_TypeDef* DMAy_Streamx)
{
  uint32_t tmpreg = 0;
 
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
  
  /* Get the FIFO level bits */
  tmpreg = (uint32_t)((DMAy_Streamx->FCR & DMA_SxFCR_FS));
  
  return tmpreg;
}