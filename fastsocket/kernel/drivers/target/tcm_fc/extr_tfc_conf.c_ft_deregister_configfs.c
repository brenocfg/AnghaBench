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
 int /*<<< orphan*/ * ft_configfs ; 
 int /*<<< orphan*/  target_fabric_configfs_deregister (int /*<<< orphan*/ *) ; 

void ft_deregister_configfs(void)
{
	if (!ft_configfs)
		return;
	target_fabric_configfs_deregister(ft_configfs);
	ft_configfs = NULL;
}