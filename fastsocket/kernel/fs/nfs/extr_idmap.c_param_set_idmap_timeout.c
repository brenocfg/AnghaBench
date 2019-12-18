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
 int HZ ; 
 int simple_strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int param_set_idmap_timeout(const char *val, struct kernel_param *kp)
{
	char *endp;
	int num = simple_strtol(val, &endp, 0);
	int jif = num * HZ;
	if (endp == val || *endp || num < 0 || jif < num)
		return -EINVAL;
	*((int *)kp->arg) = jif;
	return 0;
}