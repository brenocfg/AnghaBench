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
 int /*<<< orphan*/ * g_do_test ; 
 unsigned int g_test_ioctl ; 

__attribute__((used)) static do_test_fn *_find_ioctl(unsigned cmd)
{
	if (g_test_ioctl == cmd)
		return g_do_test;
	else
		return NULL;
}