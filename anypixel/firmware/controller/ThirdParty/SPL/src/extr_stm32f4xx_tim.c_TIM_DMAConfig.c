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
typedef  int uint16_t ;
struct TYPE_4__ {int DCR; } ;
typedef  TYPE_1__ TIM_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_DMA_BASE (int) ; 
 int /*<<< orphan*/  IS_TIM_DMA_LENGTH (int) ; 
 int /*<<< orphan*/  IS_TIM_LIST3_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_DMA_BASE(TIM_DMABase)); 
  assert_param(IS_TIM_DMA_LENGTH(TIM_DMABurstLength));

  /* Set the DMA Base and the DMA Burst Length */
  TIMx->DCR = TIM_DMABase | TIM_DMABurstLength;
}