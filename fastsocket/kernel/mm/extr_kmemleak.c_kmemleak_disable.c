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
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_work ; 
 int /*<<< orphan*/  kmemleak_early_log ; 
 int /*<<< orphan*/  kmemleak_enabled ; 
 int /*<<< orphan*/  kmemleak_error ; 
 int /*<<< orphan*/  kmemleak_initialized ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kmemleak_disable(void)
{
	/* atomically check whether it was already invoked */
	if (atomic_cmpxchg(&kmemleak_error, 0, 1))
		return;

	/* stop any memory operation tracing */
	atomic_set(&kmemleak_early_log, 0);
	atomic_set(&kmemleak_enabled, 0);

	/* check whether it is too early for a kernel thread */
	if (atomic_read(&kmemleak_initialized))
		schedule_work(&cleanup_work);

	pr_info("Kernel memory leak detector disabled\n");
}