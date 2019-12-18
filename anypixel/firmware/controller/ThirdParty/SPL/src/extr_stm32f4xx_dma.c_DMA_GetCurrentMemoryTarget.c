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
typedef  int uint32_t ;
struct TYPE_4__ {int CR; } ;
typedef  TYPE_1__ DMA_Stream_TypeDef ;

/* Variables and functions */
 int DMA_SxCR_CT ; 
 int /*<<< orphan*/  IS_DMA_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

uint32_t DMA_GetCurrentMemoryTarget(DMA_Stream_TypeDef* DMAy_Streamx)
{
  uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));

  /* Get the current memory target */
  if ((DMAy_Streamx->CR & DMA_SxCR_CT) != 0)
  {
    /* Current memory buffer used is Memory 1 */
    tmp = 1;
  }  
  else
  {
    /* Current memory buffer used is Memory 0 */
    tmp = 0;    
  }
  return tmp;
}