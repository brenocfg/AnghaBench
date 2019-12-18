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
 int /*<<< orphan*/  RDS_INFO_TCP_SOCKETS ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_info_deregister_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_tcp_conn_slab ; 
 int /*<<< orphan*/  rds_tcp_destroy_conns () ; 
 int /*<<< orphan*/  rds_tcp_listen_stop () ; 
 int /*<<< orphan*/  rds_tcp_recv_exit () ; 
 int /*<<< orphan*/  rds_tcp_tc_info ; 
 int /*<<< orphan*/  rds_tcp_transport ; 
 int /*<<< orphan*/  rds_trans_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rds_tcp_exit(void)
{
	rds_info_deregister_func(RDS_INFO_TCP_SOCKETS, rds_tcp_tc_info);
	rds_tcp_listen_stop();
	rds_tcp_destroy_conns();
	rds_trans_unregister(&rds_tcp_transport);
	rds_tcp_recv_exit();
	kmem_cache_destroy(rds_tcp_conn_slab);
}