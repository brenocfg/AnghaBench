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
typedef  int /*<<< orphan*/  do_test_fn ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * g_do_test ; 
 unsigned int g_test_ioctl ; 

int osduld_register_test(unsigned ioctl, do_test_fn *do_test)
{
	if (g_test_ioctl)
		return -EINVAL;

	g_test_ioctl = ioctl;
	g_do_test = do_test;
	return 0;
}