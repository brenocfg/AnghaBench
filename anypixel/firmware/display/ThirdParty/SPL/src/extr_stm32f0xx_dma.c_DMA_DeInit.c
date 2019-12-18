#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_13__ {scalar_t__ CMAR; scalar_t__ CPAR; scalar_t__ CNDTR; int /*<<< orphan*/  CCR; } ;
struct TYPE_12__ {int /*<<< orphan*/  IFCR; } ;
typedef  TYPE_1__ DMA_Channel_TypeDef ;

/* Variables and functions */
 TYPE_11__* DMA1 ; 
 int /*<<< orphan*/  DMA1_CHANNEL1_IT_MASK ; 
 int /*<<< orphan*/  DMA1_CHANNEL2_IT_MASK ; 
 int /*<<< orphan*/  DMA1_CHANNEL3_IT_MASK ; 
 int /*<<< orphan*/  DMA1_CHANNEL4_IT_MASK ; 
 int /*<<< orphan*/  DMA1_CHANNEL5_IT_MASK ; 
 int /*<<< orphan*/  DMA1_CHANNEL6_IT_MASK ; 
 int /*<<< orphan*/  DMA1_CHANNEL7_IT_MASK ; 
 TYPE_1__* DMA1_Channel1 ; 
 TYPE_1__* DMA1_Channel2 ; 
 TYPE_1__* DMA1_Channel3 ; 
 TYPE_1__* DMA1_Channel4 ; 
 TYPE_1__* DMA1_Channel5 ; 
 TYPE_1__* DMA1_Channel6 ; 
 TYPE_1__* DMA1_Channel7 ; 
 scalar_t__ DMA_CCR_EN ; 
 int /*<<< orphan*/  IS_DMA_ALL_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));

  /* Disable the selected DMAy Channelx */
  DMAy_Channelx->CCR &= (uint16_t)(~DMA_CCR_EN);

  /* Reset DMAy Channelx control register */
  DMAy_Channelx->CCR  = 0;

  /* Reset DMAy Channelx remaining bytes register */
  DMAy_Channelx->CNDTR = 0;

  /* Reset DMAy Channelx peripheral address register */
  DMAy_Channelx->CPAR  = 0;

  /* Reset DMAy Channelx memory address register */
  DMAy_Channelx->CMAR = 0;

  if (DMAy_Channelx == DMA1_Channel1)
  {
    /* Reset interrupt pending bits for DMA1 Channel1 */
    DMA1->IFCR |= DMA1_CHANNEL1_IT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel2)
  {
    /* Reset interrupt pending bits for DMA1 Channel2 */
    DMA1->IFCR |= DMA1_CHANNEL2_IT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel3)
  {
    /* Reset interrupt pending bits for DMA1 Channel3 */
    DMA1->IFCR |= DMA1_CHANNEL3_IT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel4)
  {
    /* Reset interrupt pending bits for DMA1 Channel4 */
    DMA1->IFCR |= DMA1_CHANNEL4_IT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel5)
  {
    /* Reset interrupt pending bits for DMA1 Channel5 */
    DMA1->IFCR |= DMA1_CHANNEL5_IT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel6)
  {
    /* Reset interrupt pending bits for DMA1 Channel6 */
    DMA1->IFCR |= DMA1_CHANNEL6_IT_MASK;
  }
  else
  {
    if (DMAy_Channelx == DMA1_Channel7) 
    {
      /* Reset interrupt pending bits for DMA1 Channel7 */
      DMA1->IFCR |= DMA1_CHANNEL7_IT_MASK;
    }
  }
}