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
typedef  int uint32_t ;
struct TYPE_3__ {int GEN_CONF; unsigned long long GINTR_STA; int /*<<< orphan*/  MAIN_CNT; int /*<<< orphan*/  TIM2_COMP; int /*<<< orphan*/  TIM2_CONF; int /*<<< orphan*/  TIM1_COMP; int /*<<< orphan*/  TIM1_CONF; int /*<<< orphan*/  TIM0_COMP; int /*<<< orphan*/  TIM0_CONF; } ;
typedef  TYPE_1__ hpetReg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ hpetArea ; 
 int hptcAE ; 
 scalar_t__ rcbaArea ; 
 TYPE_1__ saved_hpet ; 

void
hpet_restore(void)
{
	hpetReg_t	*from = &saved_hpet;
	hpetReg_t	*to = (hpetReg_t *) hpetArea;

	/*
	 * Is the HPET memory already enabled?
	 * If not, set address and enable.
	 */
	uint32_t *hptcp = (uint32_t *)(rcbaArea + 0x3404);
	uint32_t hptc = *hptcp;
	if(!(hptc & hptcAE)) {
		DBG("HPET memory is not enabled, "
		    "enabling and assigning to 0xFED00000 (hope that's ok)\n");
		*hptcp = (hptc & ~3) | hptcAE;
	}

	to->GEN_CONF  = from->GEN_CONF & ~1;

	to->TIM0_CONF = from->TIM0_CONF;
	to->TIM0_COMP = from->TIM0_COMP;
	to->TIM1_CONF = from->TIM1_CONF;
	to->TIM1_COMP = from->TIM1_COMP;
	to->TIM2_CONF = from->TIM2_CONF;
	to->TIM2_COMP = from->TIM2_COMP;
	to->GINTR_STA = -1ULL;
	to->MAIN_CNT  = from->MAIN_CNT;

	to->GEN_CONF = from->GEN_CONF;
}