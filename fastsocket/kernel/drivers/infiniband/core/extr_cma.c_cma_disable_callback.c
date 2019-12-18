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
struct rdma_id_private {int state; int /*<<< orphan*/  handler_mutex; } ;
typedef  enum rdma_cm_state { ____Placeholder_rdma_cm_state } rdma_cm_state ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cma_disable_callback(struct rdma_id_private *id_priv,
				enum rdma_cm_state state)
{
	mutex_lock(&id_priv->handler_mutex);
	if (id_priv->state != state) {
		mutex_unlock(&id_priv->handler_mutex);
		return -EINVAL;
	}
	return 0;
}