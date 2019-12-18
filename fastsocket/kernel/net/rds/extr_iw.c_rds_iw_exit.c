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
 int /*<<< orphan*/  RDS_INFO_IWARP_CONNECTIONS ; 
 int /*<<< orphan*/  ib_unregister_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_info_deregister_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_client ; 
 int /*<<< orphan*/  rds_iw_destroy_nodev_conns () ; 
 int /*<<< orphan*/  rds_iw_ic_info ; 
 int /*<<< orphan*/  rds_iw_recv_exit () ; 
 int /*<<< orphan*/  rds_iw_sysctl_exit () ; 
 int /*<<< orphan*/  rds_iw_transport ; 
 int /*<<< orphan*/  rds_trans_unregister (int /*<<< orphan*/ *) ; 

void rds_iw_exit(void)
{
	rds_info_deregister_func(RDS_INFO_IWARP_CONNECTIONS, rds_iw_ic_info);
	rds_iw_destroy_nodev_conns();
	ib_unregister_client(&rds_iw_client);
	rds_iw_sysctl_exit();
	rds_iw_recv_exit();
	rds_trans_unregister(&rds_iw_transport);
}