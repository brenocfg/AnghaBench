#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int CR; int FCR; } ;
struct TYPE_8__ {int HISR; int LISR; } ;
typedef  scalar_t__ ITStatus ;
typedef  TYPE_1__ DMA_TypeDef ;
typedef  TYPE_2__ DMA_Stream_TypeDef ;

/* Variables and functions */
 TYPE_1__* DMA1 ; 
 TYPE_1__* DMA2 ; 
 TYPE_2__* DMA2_Stream0 ; 
 int DMA_IT_FE ; 
 int HIGH_ISR_MASK ; 
 int /*<<< orphan*/  IS_DMA_ALL_PERIPH (TYPE_2__*) ; 
 int /*<<< orphan*/  IS_DMA_GET_IT (int) ; 
 scalar_t__ RESERVED_MASK ; 
 scalar_t__ RESET ; 
 scalar_t__ SET ; 
 int TRANSFER_IT_ENABLE_MASK ; 
 int TRANSFER_IT_MASK ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

ITStatus DMA_GetITStatus(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT)
{
  ITStatus bitstatus = RESET;
  DMA_TypeDef* DMAy;
  uint32_t tmpreg = 0, enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
  assert_param(IS_DMA_GET_IT(DMA_IT));
 
  /* Determine the DMA to which belongs the stream */
  if (DMAy_Streamx < DMA2_Stream0)
  {
    /* DMAy_Streamx belongs to DMA1 */
    DMAy = DMA1; 
  } 
  else 
  {
    /* DMAy_Streamx belongs to DMA2 */
    DMAy = DMA2; 
  }

  /* Check if the interrupt enable bit is in the CR or FCR register */
  if ((DMA_IT & TRANSFER_IT_MASK) != (uint32_t)RESET)
  {
    /* Get the interrupt enable position mask in CR register */
    tmpreg = (uint32_t)((DMA_IT >> 11) & TRANSFER_IT_ENABLE_MASK);   
    
    /* Check the enable bit in CR register */
    enablestatus = (uint32_t)(DMAy_Streamx->CR & tmpreg);
  }
  else 
  {
    /* Check the enable bit in FCR register */
    enablestatus = (uint32_t)(DMAy_Streamx->FCR & DMA_IT_FE); 
  }
 
  /* Check if the interrupt pending flag is in LISR or HISR */
  if ((DMA_IT & HIGH_ISR_MASK) != (uint32_t)RESET)
  {
    /* Get DMAy HISR register value */
    tmpreg = DMAy->HISR ;
  }
  else
  {
    /* Get DMAy LISR register value */
    tmpreg = DMAy->LISR ;
  } 

  /* mask all reserved bits */
  tmpreg &= (uint32_t)RESERVED_MASK;

  /* Check the status of the specified DMA interrupt */
  if (((tmpreg & DMA_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    /* DMA_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* DMA_IT is reset */
    bitstatus = RESET;
  }

  /* Return the DMA_IT status */
  return  bitstatus;
}