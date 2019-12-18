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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  period; } ;

/* Variables and functions */
 int MAX_BLACKFIN_GPTIMERS ; 
 int /*<<< orphan*/  tassert (int) ; 
 TYPE_1__** timer_regs ; 

uint32_t get_gptimer_period(int timer_id)
{
	tassert(timer_id < MAX_BLACKFIN_GPTIMERS);
	return timer_regs[timer_id]->period;
}