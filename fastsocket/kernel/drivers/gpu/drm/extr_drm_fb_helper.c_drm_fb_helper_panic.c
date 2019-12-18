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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int drm_fb_helper_force_kernel_mode () ; 
 scalar_t__ panic_timeout ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int drm_fb_helper_panic(struct notifier_block *n, unsigned long ununsed,
			void *panic_str)
{
	/*
	 * It's a waste of time and effort to switch back to text console
	 * if the kernel should reboot before panic messages can be seen.
	 */
	if (panic_timeout < 0)
		return 0;

	pr_err("panic occurred, switching back to text console\n");
	return drm_fb_helper_force_kernel_mode();
}