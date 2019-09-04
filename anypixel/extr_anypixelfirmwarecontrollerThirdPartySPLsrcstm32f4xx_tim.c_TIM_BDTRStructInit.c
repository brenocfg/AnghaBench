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
struct TYPE_3__ {int TIM_DeadTime; int /*<<< orphan*/  TIM_AutomaticOutput; int /*<<< orphan*/  TIM_BreakPolarity; int /*<<< orphan*/  TIM_Break; int /*<<< orphan*/  TIM_LOCKLevel; int /*<<< orphan*/  TIM_OSSIState; int /*<<< orphan*/  TIM_OSSRState; } ;
typedef  TYPE_1__ TIM_BDTRInitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_AutomaticOutput_Disable ; 
 int /*<<< orphan*/  TIM_BreakPolarity_Low ; 
 int /*<<< orphan*/  TIM_Break_Disable ; 
 int /*<<< orphan*/  TIM_LOCKLevel_OFF ; 
 int /*<<< orphan*/  TIM_OSSIState_Disable ; 
 int /*<<< orphan*/  TIM_OSSRState_Disable ; 

void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct)
{
  /* Set the default configuration */
  TIM_BDTRInitStruct->TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStruct->TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStruct->TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStruct->TIM_DeadTime = 0x00;
  TIM_BDTRInitStruct->TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStruct->TIM_BreakPolarity = TIM_BreakPolarity_Low;
  TIM_BDTRInitStruct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
}