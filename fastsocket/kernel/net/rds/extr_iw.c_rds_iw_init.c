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
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RDS_INFO_IWARP_CONNECTIONS ; 
 int ib_register_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_info_register_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_client ; 
 int /*<<< orphan*/  rds_iw_devices ; 
 int /*<<< orphan*/  rds_iw_ic_info ; 
 int /*<<< orphan*/  rds_iw_recv_exit () ; 
 int rds_iw_recv_init () ; 
 int /*<<< orphan*/  rds_iw_sysctl_exit () ; 
 int rds_iw_sysctl_init () ; 
 int /*<<< orphan*/  rds_iw_transport ; 
 int rds_trans_register (int /*<<< orphan*/ *) ; 

int rds_iw_init(void)
{
	int ret;

	INIT_LIST_HEAD(&rds_iw_devices);

	ret = ib_register_client(&rds_iw_client);
	if (ret)
		goto out;

	ret = rds_iw_sysctl_init();
	if (ret)
		goto out_ibreg;

	ret = rds_iw_recv_init();
	if (ret)
		goto out_sysctl;

	ret = rds_trans_register(&rds_iw_transport);
	if (ret)
		goto out_recv;

	rds_info_register_func(RDS_INFO_IWARP_CONNECTIONS, rds_iw_ic_info);

	goto out;

out_recv:
	rds_iw_recv_exit();
out_sysctl:
	rds_iw_sysctl_exit();
out_ibreg:
	ib_unregister_client(&rds_iw_client);
out:
	return ret;
}