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
struct rds_tcp_connection {int t_tinc_hdr_rem; int /*<<< orphan*/  t_tcp_node; scalar_t__ t_tinc_data_rem; int /*<<< orphan*/ * t_tinc; int /*<<< orphan*/ * t_sock; } ;
struct rds_header {int dummy; } ;
struct rds_connection {struct rds_tcp_connection* c_transport_data; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct rds_tcp_connection* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_tcp_conn_list ; 
 int /*<<< orphan*/  rds_tcp_conn_lock ; 
 int /*<<< orphan*/  rds_tcp_conn_slab ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_tcp_connection*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rds_tcp_conn_alloc(struct rds_connection *conn, gfp_t gfp)
{
	struct rds_tcp_connection *tc;

	tc = kmem_cache_alloc(rds_tcp_conn_slab, gfp);
	if (!tc)
		return -ENOMEM;

	tc->t_sock = NULL;
	tc->t_tinc = NULL;
	tc->t_tinc_hdr_rem = sizeof(struct rds_header);
	tc->t_tinc_data_rem = 0;

	conn->c_transport_data = tc;

	spin_lock_irq(&rds_tcp_conn_lock);
	list_add_tail(&tc->t_tcp_node, &rds_tcp_conn_list);
	spin_unlock_irq(&rds_tcp_conn_lock);

	rdsdebug("alloced tc %p\n", conn->c_transport_data);
	return 0;
}