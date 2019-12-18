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
struct rdma_cm_id {scalar_t__ context; } ;
struct iser_conn {scalar_t__ post_recv_buf_count; int /*<<< orphan*/  wait; int /*<<< orphan*/  state; int /*<<< orphan*/  post_send_buf_count; TYPE_1__* iser_conn; } ;
struct TYPE_2__ {int /*<<< orphan*/  iscsi_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_ERR_CONN_FAILED ; 
 int /*<<< orphan*/  ISER_CONN_DOWN ; 
 int /*<<< orphan*/  ISER_CONN_TERMINATING ; 
 int /*<<< orphan*/  ISER_CONN_UP ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_conn_failure (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iser_conn_put (struct iser_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ iser_conn_state_comp_exch (struct iser_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iser_disconnected_handler(struct rdma_cm_id *cma_id)
{
	struct iser_conn *ib_conn;
	int ret;

	ib_conn = (struct iser_conn *)cma_id->context;

	/* getting here when the state is UP means that the conn is being *
	 * terminated asynchronously from the iSCSI layer's perspective.  */
	if (iser_conn_state_comp_exch(ib_conn, ISER_CONN_UP,
				      ISER_CONN_TERMINATING))
		iscsi_conn_failure(ib_conn->iser_conn->iscsi_conn,
				   ISCSI_ERR_CONN_FAILED);

	/* Complete the termination process if no posts are pending */
	if (ib_conn->post_recv_buf_count == 0 &&
	    (atomic_read(&ib_conn->post_send_buf_count) == 0)) {
		ib_conn->state = ISER_CONN_DOWN;
		wake_up_interruptible(&ib_conn->wait);
	}

	ret = iser_conn_put(ib_conn, 0); /* deref ib conn's cma id */
	return ret;
}