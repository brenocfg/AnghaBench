#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_INFO_RECV_MESSAGES ; 
 int /*<<< orphan*/  RDS_INFO_SOCKETS ; 
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_cong_exit () ; 
 int /*<<< orphan*/  rds_conn_exit () ; 
 TYPE_1__ rds_family_ops ; 
 int /*<<< orphan*/  rds_info_deregister_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_page_exit () ; 
 int /*<<< orphan*/  rds_proto ; 
 int /*<<< orphan*/  rds_sock_inc_info ; 
 int /*<<< orphan*/  rds_sock_info ; 
 int /*<<< orphan*/  rds_stats_exit () ; 
 int /*<<< orphan*/  rds_sysctl_exit () ; 
 int /*<<< orphan*/  rds_threads_exit () ; 
 int /*<<< orphan*/  sock_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rds_exit(void)
{
	sock_unregister(rds_family_ops.family);
	proto_unregister(&rds_proto);
	rds_conn_exit();
	rds_cong_exit();
	rds_sysctl_exit();
	rds_threads_exit();
	rds_stats_exit();
	rds_page_exit();
	rds_info_deregister_func(RDS_INFO_SOCKETS, rds_sock_info);
	rds_info_deregister_func(RDS_INFO_RECV_MESSAGES, rds_sock_inc_info);
}