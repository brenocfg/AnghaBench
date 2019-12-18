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
struct rdma_id_private {int /*<<< orphan*/ * cma_dev; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  cma_deref_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cma_release_dev(struct rdma_id_private *id_priv)
{
	mutex_lock(&lock);
	list_del(&id_priv->list);
	cma_deref_dev(id_priv->cma_dev);
	id_priv->cma_dev = NULL;
	mutex_unlock(&lock);
}