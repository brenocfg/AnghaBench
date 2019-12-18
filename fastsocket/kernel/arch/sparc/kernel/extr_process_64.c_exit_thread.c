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
struct thread_info {int* utraps; scalar_t__ pcr_reg; int /*<<< orphan*/ * user_cntd1; int /*<<< orphan*/  user_cntd0; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_PERFCTR ; 
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  kfree (int*) ; 
 scalar_t__ test_and_clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pcr (int /*<<< orphan*/ ) ; 

void exit_thread(void)
{
	struct thread_info *t = current_thread_info();

	if (t->utraps) {
		if (t->utraps[0] < 2)
			kfree (t->utraps);
		else
			t->utraps[0]--;
	}

	if (test_and_clear_thread_flag(TIF_PERFCTR)) {
		t->user_cntd0 = t->user_cntd1 = NULL;
		t->pcr_reg = 0;
		write_pcr(0);
	}
}