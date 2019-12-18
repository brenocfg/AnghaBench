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
 int /*<<< orphan*/  RDS_INFO_IB_CONNECTIONS ; 
 int ib_register_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_client ; 
 int /*<<< orphan*/  rds_ib_devices ; 
 int /*<<< orphan*/  rds_ib_ic_info ; 
 int /*<<< orphan*/  rds_ib_recv_exit () ; 
 int rds_ib_recv_init () ; 
 int /*<<< orphan*/  rds_ib_sysctl_exit () ; 
 int rds_ib_sysctl_init () ; 
 int /*<<< orphan*/  rds_ib_transport ; 
 int /*<<< orphan*/  rds_ib_unregister_client () ; 
 int /*<<< orphan*/  rds_info_register_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rds_trans_register (int /*<<< orphan*/ *) ; 

int rds_ib_init(void)
{
	int ret;

	INIT_LIST_HEAD(&rds_ib_devices);

	ret = ib_register_client(&rds_ib_client);
	if (ret)
		goto out;

	ret = rds_ib_sysctl_init();
	if (ret)
		goto out_ibreg;

	ret = rds_ib_recv_init();
	if (ret)
		goto out_sysctl;

	ret = rds_trans_register(&rds_ib_transport);
	if (ret)
		goto out_recv;

	rds_info_register_func(RDS_INFO_IB_CONNECTIONS, rds_ib_ic_info);

	goto out;

out_recv:
	rds_ib_recv_exit();
out_sysctl:
	rds_ib_sysctl_exit();
out_ibreg:
	rds_ib_unregister_client();
out:
	return ret;
}