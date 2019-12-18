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
 int /*<<< orphan*/ * g_do_test ; 
 unsigned int g_test_ioctl ; 

void osduld_unregister_test(unsigned ioctl)
{
	if (ioctl == g_test_ioctl) {
		g_test_ioctl = 0;
		g_do_test = NULL;
	}
}