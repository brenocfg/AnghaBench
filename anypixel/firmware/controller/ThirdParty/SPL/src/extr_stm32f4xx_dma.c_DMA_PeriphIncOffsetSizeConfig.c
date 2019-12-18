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
struct TYPE_4__ {scalar_t__ CR; } ;
typedef  TYPE_1__ DMA_Stream_TypeDef ;

/* Variables and functions */
 scalar_t__ DMA_PINCOS_Psize ; 
 scalar_t__ DMA_SxCR_PINCOS ; 
 int /*<<< orphan*/  IS_DMA_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_DMA_PINCOS_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void DMA_PeriphIncOffsetSizeConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_Pincos)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
  assert_param(IS_DMA_PINCOS_SIZE(DMA_Pincos));

  /* Check the needed Peripheral increment offset */
  if(DMA_Pincos != DMA_PINCOS_Psize)
  {
    /* Configure DMA_SxCR_PINCOS bit with the input parameter */
    DMAy_Streamx->CR |= (uint32_t)DMA_SxCR_PINCOS;     
  }
  else
  {
    /* Clear the PINCOS bit: Peripheral address incremented according to PSIZE */
    DMAy_Streamx->CR &= ~(uint32_t)DMA_SxCR_PINCOS;    
  }
}