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
 scalar_t__ DMA_FlowCtrl_Memory ; 
 scalar_t__ DMA_SxCR_PFCTRL ; 
 int /*<<< orphan*/  IS_DMA_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_DMA_FLOW_CTRL (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void DMA_FlowControllerConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FlowCtrl)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
  assert_param(IS_DMA_FLOW_CTRL(DMA_FlowCtrl));

  /* Check the needed flow controller  */
  if(DMA_FlowCtrl != DMA_FlowCtrl_Memory)
  {
    /* Configure DMA_SxCR_PFCTRL bit with the input parameter */
    DMAy_Streamx->CR |= (uint32_t)DMA_SxCR_PFCTRL;   
  }
  else
  {
    /* Clear the PFCTRL bit: Memory is the flow controller */
    DMAy_Streamx->CR &= ~(uint32_t)DMA_SxCR_PFCTRL;    
  }
}