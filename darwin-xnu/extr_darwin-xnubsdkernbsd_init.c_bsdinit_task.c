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
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  bsd_init_kprintf (char*) ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  load_init_program (int /*<<< orphan*/ ) ; 
 int lock_trace ; 
 int /*<<< orphan*/  process_name (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ux_handler_setup () ; 
 int /*<<< orphan*/  vm_init_before_launchd () ; 

void
bsdinit_task(void)
{
	proc_t p = current_proc();

	process_name("init", p);

	/* Set up exception-to-signal reflection */
	ux_handler_setup();

#if CONFIG_MACF
	mac_cred_label_associate_user(p->p_ucred);
#endif

    vm_init_before_launchd();

#if CONFIG_XNUPOST
	int result = bsd_list_tests();
	result = bsd_do_post();
	if (result != 0) {
		panic("bsd_do_post: Tests failed with result = 0x%08x\n", result);
	}
#endif

	bsd_init_kprintf("bsd_do_post - done");

	load_init_program(p);
	lock_trace = 1;
}