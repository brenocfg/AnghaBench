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
struct TYPE_2__ {int (* event_handler ) (TYPE_1__*,struct rdma_cm_event*) ;} ;
struct rdma_id_private {int /*<<< orphan*/  handler_mutex; TYPE_1__ id; } ;
struct rdma_cm_event {int /*<<< orphan*/  event; } ;
typedef  enum rdma_cm_state { ____Placeholder_rdma_cm_state } rdma_cm_state ;

/* Variables and functions */
 int RDMA_CM_DESTROYING ; 
 int /*<<< orphan*/  RDMA_CM_DEVICE_REMOVAL ; 
 int /*<<< orphan*/  RDMA_CM_EVENT_DEVICE_REMOVAL ; 
 int /*<<< orphan*/  cma_cancel_operation (struct rdma_id_private*,int) ; 
 int /*<<< orphan*/  cma_comp (struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int cma_exch (struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rdma_cm_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,struct rdma_cm_event*) ; 

__attribute__((used)) static int cma_remove_id_dev(struct rdma_id_private *id_priv)
{
	struct rdma_cm_event event;
	enum rdma_cm_state state;
	int ret = 0;

	/* Record that we want to remove the device */
	state = cma_exch(id_priv, RDMA_CM_DEVICE_REMOVAL);
	if (state == RDMA_CM_DESTROYING)
		return 0;

	cma_cancel_operation(id_priv, state);
	mutex_lock(&id_priv->handler_mutex);

	/* Check for destruction from another callback. */
	if (!cma_comp(id_priv, RDMA_CM_DEVICE_REMOVAL))
		goto out;

	memset(&event, 0, sizeof event);
	event.event = RDMA_CM_EVENT_DEVICE_REMOVAL;
	ret = id_priv->id.event_handler(&id_priv->id, &event);
out:
	mutex_unlock(&id_priv->handler_mutex);
	return ret;
}