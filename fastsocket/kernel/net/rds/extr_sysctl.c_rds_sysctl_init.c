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
 int ENOMEM ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  rds_sysctl_path ; 
 int /*<<< orphan*/  rds_sysctl_rds_table ; 
 int /*<<< orphan*/  rds_sysctl_reconnect_min ; 
 int /*<<< orphan*/  rds_sysctl_reconnect_min_jiffies ; 
 int /*<<< orphan*/  rds_sysctl_reg_table ; 
 int /*<<< orphan*/  register_net_sysctl_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rds_sysctl_init(void)
{
	rds_sysctl_reconnect_min = msecs_to_jiffies(1);
	rds_sysctl_reconnect_min_jiffies = rds_sysctl_reconnect_min;

	rds_sysctl_reg_table = register_net_sysctl_table(&init_net, rds_sysctl_path, rds_sysctl_rds_table);
	if (!rds_sysctl_reg_table)
		return -ENOMEM;
	return 0;
}