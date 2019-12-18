#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  TIMER0bit ; 
 int /*<<< orphan*/  TIMER1bit ; 
 int /*<<< orphan*/  enable_gptimers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void bfin_t350mcqb_start_timers(void)
{
	unsigned long flags;

	local_irq_save(flags);
		enable_gptimers(TIMER1bit);
		enable_gptimers(TIMER0bit);
	local_irq_restore(flags);
}