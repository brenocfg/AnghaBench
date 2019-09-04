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
struct TYPE_3__ {int /*<<< orphan*/  EXTI_LineCmd; int /*<<< orphan*/  EXTI_Trigger; int /*<<< orphan*/  EXTI_Mode; int /*<<< orphan*/  EXTI_Line; } ;
typedef  TYPE_1__ EXTI_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  EXTI_LINENONE ; 
 int /*<<< orphan*/  EXTI_Mode_Interrupt ; 
 int /*<<< orphan*/  EXTI_Trigger_Falling ; 

void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_Line = EXTI_LINENONE;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}