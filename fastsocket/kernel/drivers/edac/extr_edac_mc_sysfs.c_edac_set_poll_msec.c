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
struct kernel_param {scalar_t__ arg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  edac_mc_reset_delay_period (long) ; 
 int strict_strtol (char const*,int /*<<< orphan*/ ,long*) ; 

__attribute__((used)) static int edac_set_poll_msec(const char *val, struct kernel_param *kp)
{
	long l;
	int ret;

	if (!val)
		return -EINVAL;

	ret = strict_strtol(val, 0, &l);
	if (ret == -EINVAL || ((int)l != l))
		return -EINVAL;
	*((int *)kp->arg) = l;

	/* notify edac_mc engine to reset the poll period */
	edac_mc_reset_delay_period(l);

	return 0;
}