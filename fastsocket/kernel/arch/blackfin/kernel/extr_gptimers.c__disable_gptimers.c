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
struct TYPE_2__ {int disable; } ;

/* Variables and functions */
 int BFIN_TIMER_NUM_GROUP ; 
 int BLACKFIN_GPTIMER_IDMASK ; 
 TYPE_1__** group_regs ; 
 int /*<<< orphan*/  tassert (int) ; 

__attribute__((used)) static void _disable_gptimers(uint16_t mask)
{
	int i;
	uint16_t m = mask;
	tassert((mask & ~BLACKFIN_GPTIMER_IDMASK) == 0);
	for (i = 0; i < BFIN_TIMER_NUM_GROUP; ++i) {
		group_regs[i]->disable = m & 0xFF;
		m >>= 8;
	}
}