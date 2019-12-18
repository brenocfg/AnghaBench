#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 size_t BFIN_TIMER_OCTET (int) ; 
 int MAX_BLACKFIN_GPTIMERS ; 
 int /*<<< orphan*/  SSYNC () ; 
 int /*<<< orphan*/  _disable_gptimers (int) ; 
 TYPE_1__** group_regs ; 
 int /*<<< orphan*/ * trun_mask ; 

void disable_gptimers(uint16_t mask)
{
	int i;
	_disable_gptimers(mask);
	for (i = 0; i < MAX_BLACKFIN_GPTIMERS; ++i)
		if (mask & (1 << i))
			group_regs[BFIN_TIMER_OCTET(i)]->status |= trun_mask[i];
	SSYNC();
}