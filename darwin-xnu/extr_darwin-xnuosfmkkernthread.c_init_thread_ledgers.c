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
typedef  int /*<<< orphan*/ * ledger_template_t ;
struct TYPE_2__ {int cpu_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int ledger_entry_add (int /*<<< orphan*/ *,char*,char*,char*) ; 
 scalar_t__ ledger_set_callback (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ledger_template_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ledger_template_create (char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  thread_cputime_callback ; 
 int /*<<< orphan*/ * thread_ledger_template ; 
 TYPE_1__ thread_ledgers ; 

__attribute__((used)) static void
init_thread_ledgers(void) {
	ledger_template_t t;
	int idx;
	
	assert(thread_ledger_template == NULL);

	if ((t = ledger_template_create("Per-thread ledger")) == NULL)
		panic("couldn't create thread ledger template");

	if ((idx = ledger_entry_add(t, "cpu_time", "sched", "ns")) < 0) {
		panic("couldn't create cpu_time entry for thread ledger template");
	}

	if (ledger_set_callback(t, idx, thread_cputime_callback, NULL, NULL) < 0) {
	    	panic("couldn't set thread ledger callback for cpu_time entry");
	}

	thread_ledgers.cpu_time = idx;

	ledger_template_complete(t);
	thread_ledger_template = t;
}