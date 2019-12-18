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
struct ib_device {int dummy; } ;
struct ib_cm_id {int remote_cm_qpn; void* context; int /*<<< orphan*/  cm_handler; struct ib_device* device; int /*<<< orphan*/  state; } ;
struct cm_id_private {struct ib_cm_id id; int /*<<< orphan*/  refcount; int /*<<< orphan*/  work_count; int /*<<< orphan*/  work_list; int /*<<< orphan*/  comp; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  ib_cm_handler ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_cm_id* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_CM_IDLE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int cm_alloc_id (struct cm_id_private*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cm_id_private*) ; 
 struct cm_id_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ib_cm_id *ib_create_cm_id(struct ib_device *device,
				 ib_cm_handler cm_handler,
				 void *context)
{
	struct cm_id_private *cm_id_priv;
	int ret;

	cm_id_priv = kzalloc(sizeof *cm_id_priv, GFP_KERNEL);
	if (!cm_id_priv)
		return ERR_PTR(-ENOMEM);

	cm_id_priv->id.state = IB_CM_IDLE;
	cm_id_priv->id.device = device;
	cm_id_priv->id.cm_handler = cm_handler;
	cm_id_priv->id.context = context;
	cm_id_priv->id.remote_cm_qpn = 1;
	ret = cm_alloc_id(cm_id_priv);
	if (ret)
		goto error;

	spin_lock_init(&cm_id_priv->lock);
	init_completion(&cm_id_priv->comp);
	INIT_LIST_HEAD(&cm_id_priv->work_list);
	atomic_set(&cm_id_priv->work_count, -1);
	atomic_set(&cm_id_priv->refcount, 1);
	return &cm_id_priv->id;

error:
	kfree(cm_id_priv);
	return ERR_PTR(-ENOMEM);
}