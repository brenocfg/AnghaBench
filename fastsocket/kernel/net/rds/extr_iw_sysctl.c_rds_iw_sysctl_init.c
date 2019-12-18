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
 int /*<<< orphan*/  rds_iw_sysctl_hdr ; 
 int /*<<< orphan*/  rds_iw_sysctl_path ; 
 int /*<<< orphan*/  rds_iw_sysctl_table ; 
 int /*<<< orphan*/  register_net_sysctl_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rds_iw_sysctl_init(void)
{
	rds_iw_sysctl_hdr = register_net_sysctl_table(&init_net, rds_iw_sysctl_path, rds_iw_sysctl_table);
	if (!rds_iw_sysctl_hdr)
		return -ENOMEM;
	return 0;
}