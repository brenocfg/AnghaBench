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
typedef  int /*<<< orphan*/  gifconf_func_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NPROTO ; 
 int /*<<< orphan*/ ** gifconf_list ; 

int register_gifconf(unsigned int family, gifconf_func_t *gifconf)
{
	if (family >= NPROTO)
		return -EINVAL;
	gifconf_list[family] = gifconf;
	return 0;
}