#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  ud; } ;
struct TYPE_6__ {scalar_t__ event; TYPE_1__ param; int /*<<< orphan*/  status; } ;
struct ucma_event {int /*<<< orphan*/  list; TYPE_2__ resp; struct rdma_cm_id* cm_id; } ;
struct ucma_context {TYPE_4__* file; int /*<<< orphan*/  uid; int /*<<< orphan*/  backlog; } ;
struct rdma_cm_id {scalar_t__ qp_type; struct ucma_context* context; } ;
struct TYPE_7__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  ud; } ;
struct rdma_cm_event {scalar_t__ event; TYPE_3__ param; int /*<<< orphan*/  status; } ;
struct TYPE_8__ {int /*<<< orphan*/  mut; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  event_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_QPT_UD ; 
 scalar_t__ RDMA_CM_EVENT_CONNECT_REQUEST ; 
 int /*<<< orphan*/  kfree (struct ucma_event*) ; 
 struct ucma_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucma_copy_conn_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucma_copy_ud_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucma_set_event_context (struct ucma_context*,struct rdma_cm_event*,struct ucma_event*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ucma_event_handler(struct rdma_cm_id *cm_id,
			      struct rdma_cm_event *event)
{
	struct ucma_event *uevent;
	struct ucma_context *ctx = cm_id->context;
	int ret = 0;

	uevent = kzalloc(sizeof(*uevent), GFP_KERNEL);
	if (!uevent)
		return event->event == RDMA_CM_EVENT_CONNECT_REQUEST;

	mutex_lock(&ctx->file->mut);
	uevent->cm_id = cm_id;
	ucma_set_event_context(ctx, event, uevent);
	uevent->resp.event = event->event;
	uevent->resp.status = event->status;
	if (cm_id->qp_type == IB_QPT_UD)
		ucma_copy_ud_event(&uevent->resp.param.ud, &event->param.ud);
	else
		ucma_copy_conn_event(&uevent->resp.param.conn,
				     &event->param.conn);

	if (event->event == RDMA_CM_EVENT_CONNECT_REQUEST) {
		if (!ctx->backlog) {
			ret = -ENOMEM;
			kfree(uevent);
			goto out;
		}
		ctx->backlog--;
	} else if (!ctx->uid) {
		/*
		 * We ignore events for new connections until userspace has set
		 * their context.  This can only happen if an error occurs on a
		 * new connection before the user accepts it.  This is okay,
		 * since the accept will just fail later.
		 */
		kfree(uevent);
		goto out;
	}

	list_add_tail(&uevent->list, &ctx->file->event_list);
	wake_up_interruptible(&ctx->file->poll_wait);
out:
	mutex_unlock(&ctx->file->mut);
	return ret;
}