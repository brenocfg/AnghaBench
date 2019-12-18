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
struct rds_tcp_connection {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RDS_INFO_TCP_SOCKETS ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_info_register_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_tcp_conn_slab ; 
 int rds_tcp_listen_init () ; 
 int /*<<< orphan*/  rds_tcp_recv_exit () ; 
 int rds_tcp_recv_init () ; 
 int /*<<< orphan*/  rds_tcp_tc_info ; 
 int /*<<< orphan*/  rds_tcp_transport ; 
 int rds_trans_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_trans_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rds_tcp_init(void)
{
	int ret;

	rds_tcp_conn_slab = kmem_cache_create("rds_tcp_connection",
					      sizeof(struct rds_tcp_connection),
					      0, 0, NULL);
	if (!rds_tcp_conn_slab) {
		ret = -ENOMEM;
		goto out;
	}

	ret = rds_tcp_recv_init();
	if (ret)
		goto out_slab;

	ret = rds_trans_register(&rds_tcp_transport);
	if (ret)
		goto out_recv;

	ret = rds_tcp_listen_init();
	if (ret)
		goto out_register;

	rds_info_register_func(RDS_INFO_TCP_SOCKETS, rds_tcp_tc_info);

	goto out;

out_register:
	rds_trans_unregister(&rds_tcp_transport);
out_recv:
	rds_tcp_recv_exit();
out_slab:
	kmem_cache_destroy(rds_tcp_conn_slab);
out:
	return ret;
}