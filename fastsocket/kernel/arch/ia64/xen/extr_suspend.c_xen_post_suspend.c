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
 int /*<<< orphan*/  xen_ia64_enable_opt_feature () ; 

void
xen_post_suspend(int suspend_cancelled)
{
	if (suspend_cancelled)
		return;

	xen_ia64_enable_opt_feature();
	/* add more if necessary */
}