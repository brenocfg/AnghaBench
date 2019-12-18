#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nouveau_object {int dummy; } ;
struct nouveau_engine {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; scalar_t__ size; } ;
struct nouveau_engctx {TYPE_3__ base; int /*<<< orphan*/  head; int /*<<< orphan*/  vma; } ;
struct nouveau_client {TYPE_1__* vm; } ;
struct TYPE_5__ {struct nouveau_object* engine; } ;
struct TYPE_4__ {int /*<<< orphan*/ * engref; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct nouveau_client* nouveau_client (struct nouveau_engctx*) ; 
 int /*<<< orphan*/  nouveau_gpuobj_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  nouveau_gpuobj_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_object_destroy (int /*<<< orphan*/ *) ; 
 size_t nv_engidx (struct nouveau_object*) ; 
 struct nouveau_engine* nv_engine (struct nouveau_object*) ; 
 TYPE_2__* nv_object (struct nouveau_engctx*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
nouveau_engctx_destroy(struct nouveau_engctx *engctx)
{
	struct nouveau_object *engobj = nv_object(engctx)->engine;
	struct nouveau_engine *engine = nv_engine(engobj);
	struct nouveau_client *client = nouveau_client(engctx);
	unsigned long save;

	nouveau_gpuobj_unmap(&engctx->vma);
	spin_lock_irqsave(&engine->lock, save);
	list_del(&engctx->head);
	spin_unlock_irqrestore(&engine->lock, save);

	if (client->vm)
		atomic_dec(&client->vm->engref[nv_engidx(engobj)]);

	if (engctx->base.size)
		nouveau_gpuobj_destroy(&engctx->base);
	else
		nouveau_object_destroy(&engctx->base.base);
}