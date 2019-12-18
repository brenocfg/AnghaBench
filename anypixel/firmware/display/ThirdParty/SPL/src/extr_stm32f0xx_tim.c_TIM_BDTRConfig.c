#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int TIM_OSSIState; int TIM_LOCKLevel; int TIM_Break; int TIM_BreakPolarity; int TIM_AutomaticOutput; int TIM_DeadTime; scalar_t__ TIM_OSSRState; } ;
struct TYPE_6__ {int BDTR; } ;
typedef  TYPE_1__ TIM_TypeDef ;
typedef  TYPE_2__ TIM_BDTRInitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TIM_AUTOMATIC_OUTPUT_STATE (int) ; 
 int /*<<< orphan*/  IS_TIM_BREAK_POLARITY (int) ; 
 int /*<<< orphan*/  IS_TIM_BREAK_STATE (int) ; 
 int /*<<< orphan*/  IS_TIM_LIST2_PERIPH (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_TIM_LOCK_LEVEL (int) ; 
 int /*<<< orphan*/  IS_TIM_OSSI_STATE (int) ; 
 int /*<<< orphan*/  IS_TIM_OSSR_STATE (scalar_t__) ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TIM_LIST2_PERIPH(TIMx));
  assert_param(IS_TIM_OSSR_STATE(TIM_BDTRInitStruct->TIM_OSSRState));
  assert_param(IS_TIM_OSSI_STATE(TIM_BDTRInitStruct->TIM_OSSIState));
  assert_param(IS_TIM_LOCK_LEVEL(TIM_BDTRInitStruct->TIM_LOCKLevel));
  assert_param(IS_TIM_BREAK_STATE(TIM_BDTRInitStruct->TIM_Break));
  assert_param(IS_TIM_BREAK_POLARITY(TIM_BDTRInitStruct->TIM_BreakPolarity));
  assert_param(IS_TIM_AUTOMATIC_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_AutomaticOutput));
  /* Set the Lock level, the Break enable Bit and the Ploarity, the OSSR State,
     the OSSI State, the dead time value and the Automatic Output Enable Bit */
  TIMx->BDTR = (uint32_t)TIM_BDTRInitStruct->TIM_OSSRState | TIM_BDTRInitStruct->TIM_OSSIState |
             TIM_BDTRInitStruct->TIM_LOCKLevel | TIM_BDTRInitStruct->TIM_DeadTime |
             TIM_BDTRInitStruct->TIM_Break | TIM_BDTRInitStruct->TIM_BreakPolarity |
             TIM_BDTRInitStruct->TIM_AutomaticOutput;
}