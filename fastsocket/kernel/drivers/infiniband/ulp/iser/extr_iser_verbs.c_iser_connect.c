#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct iser_conn {scalar_t__ state; int /*<<< orphan*/ * cma_id; int /*<<< orphan*/  conn_list; int /*<<< orphan*/  wait; int /*<<< orphan*/ * device; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  connlist_mutex; int /*<<< orphan*/  connlist; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IB_QPT_RC ; 
 scalar_t__ ISER_CONN_DOWN ; 
 scalar_t__ ISER_CONN_PENDING ; 
 scalar_t__ ISER_CONN_UP ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RDMA_PS_TCP ; 
 TYPE_2__ ig ; 
 int /*<<< orphan*/  iser_cma_handler ; 
 int /*<<< orphan*/  iser_conn_get (struct iser_conn*) ; 
 int /*<<< orphan*/  iser_conn_put (struct iser_conn*,int) ; 
 int /*<<< orphan*/  iser_err (char*,int) ; 
 int /*<<< orphan*/  iser_info (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rdma_create_id (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_resolve_addr (int /*<<< orphan*/ *,struct sockaddr*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int iser_connect(struct iser_conn   *ib_conn,
		 struct sockaddr_in *src_addr,
		 struct sockaddr_in *dst_addr,
		 int                 non_blocking)
{
	struct sockaddr *src, *dst;
	int err = 0;

	sprintf(ib_conn->name, "%pI4:%d",
		&dst_addr->sin_addr.s_addr, dst_addr->sin_port);

	/* the device is known only --after-- address resolution */
	ib_conn->device = NULL;

	iser_info("connecting to: %pI4, port 0x%x\n",
		  &dst_addr->sin_addr, dst_addr->sin_port);

	ib_conn->state = ISER_CONN_PENDING;

	iser_conn_get(ib_conn); /* ref ib conn's cma id */
	ib_conn->cma_id = rdma_create_id(iser_cma_handler,
					     (void *)ib_conn,
					     RDMA_PS_TCP, IB_QPT_RC);
	if (IS_ERR(ib_conn->cma_id)) {
		err = PTR_ERR(ib_conn->cma_id);
		iser_err("rdma_create_id failed: %d\n", err);
		goto id_failure;
	}

	src = (struct sockaddr *)src_addr;
	dst = (struct sockaddr *)dst_addr;
	err = rdma_resolve_addr(ib_conn->cma_id, src, dst, 1000);
	if (err) {
		iser_err("rdma_resolve_addr failed: %d\n", err);
		goto addr_failure;
	}

	if (!non_blocking) {
		wait_event_interruptible(ib_conn->wait,
					 (ib_conn->state != ISER_CONN_PENDING));

		if (ib_conn->state != ISER_CONN_UP) {
			err =  -EIO;
			goto connect_failure;
		}
	}

	mutex_lock(&ig.connlist_mutex);
	list_add(&ib_conn->conn_list, &ig.connlist);
	mutex_unlock(&ig.connlist_mutex);
	return 0;

id_failure:
	ib_conn->cma_id = NULL;
addr_failure:
	ib_conn->state = ISER_CONN_DOWN;
	iser_conn_put(ib_conn, 1); /* deref ib conn's cma id */
connect_failure:
	iser_conn_put(ib_conn, 1); /* deref ib conn deallocate */
	return err;
}