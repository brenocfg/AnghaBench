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
 int /*<<< orphan*/  RDS_INFO_RECV_MESSAGES ; 
 int /*<<< orphan*/  RDS_INFO_SOCKETS ; 
 int proto_register (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_cong_exit () ; 
 int /*<<< orphan*/  rds_conn_exit () ; 
 int rds_conn_init () ; 
 int /*<<< orphan*/  rds_family_ops ; 
 int /*<<< orphan*/  rds_info_register_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_page_exit () ; 
 int /*<<< orphan*/  rds_proto ; 
 int /*<<< orphan*/  rds_sock_inc_info ; 
 int /*<<< orphan*/  rds_sock_info ; 
 int /*<<< orphan*/  rds_stats_exit () ; 
 int rds_stats_init () ; 
 int /*<<< orphan*/  rds_sysctl_exit () ; 
 int rds_sysctl_init () ; 
 int /*<<< orphan*/  rds_threads_exit () ; 
 int rds_threads_init () ; 
 int sock_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rds_init(void)
{
	int ret;

	ret = rds_conn_init();
	if (ret)
		goto out;
	ret = rds_threads_init();
	if (ret)
		goto out_conn;
	ret = rds_sysctl_init();
	if (ret)
		goto out_threads;
	ret = rds_stats_init();
	if (ret)
		goto out_sysctl;
	ret = proto_register(&rds_proto, 1);
	if (ret)
		goto out_stats;
	ret = sock_register(&rds_family_ops);
	if (ret)
		goto out_proto;

	rds_info_register_func(RDS_INFO_SOCKETS, rds_sock_info);
	rds_info_register_func(RDS_INFO_RECV_MESSAGES, rds_sock_inc_info);

	goto out;

out_proto:
	proto_unregister(&rds_proto);
out_stats:
	rds_stats_exit();
out_sysctl:
	rds_sysctl_exit();
out_threads:
	rds_threads_exit();
out_conn:
	rds_conn_exit();
	rds_cong_exit();
	rds_page_exit();
out:
	return ret;
}