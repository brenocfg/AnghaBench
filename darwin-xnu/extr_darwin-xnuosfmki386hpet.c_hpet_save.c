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
struct TYPE_3__ {int /*<<< orphan*/  MAIN_CNT; int /*<<< orphan*/  TIM2_COMP; int /*<<< orphan*/  TIM2_CONF; int /*<<< orphan*/  TIM1_COMP; int /*<<< orphan*/  TIM1_CONF; int /*<<< orphan*/  TIM0_COMP; int /*<<< orphan*/  TIM0_CONF; int /*<<< orphan*/  GEN_CONF; } ;
typedef  TYPE_1__ hpetReg_t ;

/* Variables and functions */
 scalar_t__ hpetArea ; 
 TYPE_1__ saved_hpet ; 

void
hpet_save(void)
{
	hpetReg_t	*from = (hpetReg_t *) hpetArea;
	hpetReg_t	*to = &saved_hpet;

	to->GEN_CONF  = from->GEN_CONF;
	to->TIM0_CONF = from->TIM0_CONF;
	to->TIM0_COMP = from->TIM0_COMP;
	to->TIM1_CONF = from->TIM1_CONF;
	to->TIM1_COMP = from->TIM1_COMP;
	to->TIM2_CONF = from->TIM2_CONF;
	to->TIM2_COMP = from->TIM2_COMP;
	to->MAIN_CNT  = from->MAIN_CNT;
}