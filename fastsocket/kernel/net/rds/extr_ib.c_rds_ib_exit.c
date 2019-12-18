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
 int /*<<< orphan*/  RDS_INFO_IB_CONNECTIONS ; 
 int /*<<< orphan*/  rds_ib_destroy_nodev_conns () ; 
 int /*<<< orphan*/  rds_ib_ic_info ; 
 int /*<<< orphan*/  rds_ib_recv_exit () ; 
 int /*<<< orphan*/  rds_ib_sysctl_exit () ; 
 int /*<<< orphan*/  rds_ib_transport ; 
 int /*<<< orphan*/  rds_ib_unregister_client () ; 
 int /*<<< orphan*/  rds_info_deregister_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_trans_unregister (int /*<<< orphan*/ *) ; 

void rds_ib_exit(void)
{
	rds_info_deregister_func(RDS_INFO_IB_CONNECTIONS, rds_ib_ic_info);
	rds_ib_unregister_client();
	rds_ib_destroy_nodev_conns();
	rds_ib_sysctl_exit();
	rds_ib_recv_exit();
	rds_trans_unregister(&rds_ib_transport);
}