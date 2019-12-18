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
struct rdma_id_private {int /*<<< orphan*/  node; struct rdma_bind_list* bind_list; } ;
struct rdma_bind_list {int /*<<< orphan*/  port; int /*<<< orphan*/  ps; int /*<<< orphan*/  owners; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rdma_bind_list*) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cma_release_port(struct rdma_id_private *id_priv)
{
	struct rdma_bind_list *bind_list = id_priv->bind_list;

	if (!bind_list)
		return;

	mutex_lock(&lock);
	hlist_del(&id_priv->node);
	if (hlist_empty(&bind_list->owners)) {
		idr_remove(bind_list->ps, bind_list->port);
		kfree(bind_list);
	}
	mutex_unlock(&lock);
}