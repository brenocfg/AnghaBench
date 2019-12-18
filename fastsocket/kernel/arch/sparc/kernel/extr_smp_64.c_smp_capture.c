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
 int atomic_add_ret (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int num_online_cpus () ; 
 int penguins_are_doing_time ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  smp_capture_depth ; 
 int /*<<< orphan*/  smp_capture_registry ; 
 int /*<<< orphan*/  smp_cross_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  xcall_capture ; 

void smp_capture(void)
{
	int result = atomic_add_ret(1, &smp_capture_depth);

	if (result == 1) {
		int ncpus = num_online_cpus();

#ifdef CAPTURE_DEBUG
		printk("CPU[%d]: Sending penguins to jail...",
		       smp_processor_id());
#endif
		penguins_are_doing_time = 1;
		atomic_inc(&smp_capture_registry);
		smp_cross_call(&xcall_capture, 0, 0, 0);
		while (atomic_read(&smp_capture_registry) != ncpus)
			rmb();
#ifdef CAPTURE_DEBUG
		printk("done\n");
#endif
	}
}