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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int cmm_disabled ; 
 int /*<<< orphan*/  cmm_free_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmm_thread ; 
 int /*<<< orphan*/ * cmm_thread_ptr ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loaned_pages ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cmm_set_disable(const char *val, struct kernel_param *kp)
{
	int disable = simple_strtoul(val, NULL, 10);

	if (disable != 0 && disable != 1)
		return -EINVAL;

	if (disable && !cmm_disabled) {
		if (cmm_thread_ptr)
			kthread_stop(cmm_thread_ptr);
		cmm_thread_ptr = NULL;
		cmm_free_pages(loaned_pages);
	} else if (!disable && cmm_disabled) {
		cmm_thread_ptr = kthread_run(cmm_thread, NULL, "cmmthread");
		if (IS_ERR(cmm_thread_ptr))
			return PTR_ERR(cmm_thread_ptr);
	}

	cmm_disabled = disable;
	return 0;
}