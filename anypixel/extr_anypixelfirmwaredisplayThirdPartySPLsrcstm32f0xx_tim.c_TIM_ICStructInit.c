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
struct TYPE_3__ {int TIM_ICFilter; int /*<<< orphan*/  TIM_ICPrescaler; int /*<<< orphan*/  TIM_ICSelection; int /*<<< orphan*/  TIM_ICPolarity; int /*<<< orphan*/  TIM_Channel; } ;
typedef  TYPE_1__ TIM_ICInitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_Channel_1 ; 
 int /*<<< orphan*/  TIM_ICPSC_DIV1 ; 
 int /*<<< orphan*/  TIM_ICPolarity_Rising ; 
 int /*<<< orphan*/  TIM_ICSelection_DirectTI ; 

void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  /* Set the default configuration */
  TIM_ICInitStruct->TIM_Channel = TIM_Channel_1;
  TIM_ICInitStruct->TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStruct->TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct->TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct->TIM_ICFilter = 0x00;
}