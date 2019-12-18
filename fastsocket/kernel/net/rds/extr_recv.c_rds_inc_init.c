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
struct rds_incoming {scalar_t__ i_rdma_cookie; int /*<<< orphan*/  i_saddr; struct rds_connection* i_conn; int /*<<< orphan*/  i_item; int /*<<< orphan*/  i_refcount; } ;
struct rds_connection {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

void rds_inc_init(struct rds_incoming *inc, struct rds_connection *conn,
		  __be32 saddr)
{
	atomic_set(&inc->i_refcount, 1);
	INIT_LIST_HEAD(&inc->i_item);
	inc->i_conn = conn;
	inc->i_saddr = saddr;
	inc->i_rdma_cookie = 0;
}