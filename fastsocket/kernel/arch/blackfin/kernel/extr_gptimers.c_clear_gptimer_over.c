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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 size_t BFIN_TIMER_OCTET (int) ; 
 int MAX_BLACKFIN_GPTIMERS ; 
 TYPE_1__** group_regs ; 
 int /*<<< orphan*/  tassert (int) ; 
 int /*<<< orphan*/ * tovf_mask ; 

void clear_gptimer_over(int timer_id)
{
	tassert(timer_id < MAX_BLACKFIN_GPTIMERS);
	group_regs[BFIN_TIMER_OCTET(timer_id)]->status = tovf_mask[timer_id];
}