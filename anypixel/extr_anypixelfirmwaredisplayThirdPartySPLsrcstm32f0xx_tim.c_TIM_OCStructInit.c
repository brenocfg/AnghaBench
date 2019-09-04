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
struct TYPE_3__ {int TIM_Pulse; int /*<<< orphan*/  TIM_OCNIdleState; int /*<<< orphan*/  TIM_OCIdleState; void* TIM_OCNPolarity; void* TIM_OCPolarity; int /*<<< orphan*/  TIM_OutputNState; int /*<<< orphan*/  TIM_OutputState; int /*<<< orphan*/  TIM_OCMode; } ;
typedef  TYPE_1__ TIM_OCInitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_OCIdleState_Reset ; 
 int /*<<< orphan*/  TIM_OCMode_Timing ; 
 int /*<<< orphan*/  TIM_OCNIdleState_Reset ; 
 void* TIM_OCPolarity_High ; 
 int /*<<< orphan*/  TIM_OutputNState_Disable ; 
 int /*<<< orphan*/  TIM_OutputState_Disable ; 

void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  /* Set the default configuration */
  TIM_OCInitStruct->TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStruct->TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStruct->TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct->TIM_Pulse = 0x0000000;
  TIM_OCInitStruct->TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCNPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStruct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}