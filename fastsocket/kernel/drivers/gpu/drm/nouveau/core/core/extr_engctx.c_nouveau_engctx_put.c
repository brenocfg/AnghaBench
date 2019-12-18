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
struct nouveau_object {int /*<<< orphan*/  engine; } ;
struct nouveau_engine {int /*<<< orphan*/  lock; } ;
struct nouveau_engctx {int /*<<< orphan*/  save; } ;

/* Variables and functions */
 struct nouveau_engctx* nv_engctx (struct nouveau_object*) ; 
 struct nouveau_engine* nv_engine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
nouveau_engctx_put(struct nouveau_object *object)
{
	if (object) {
		struct nouveau_engine *engine = nv_engine(object->engine);
		struct nouveau_engctx *engctx = nv_engctx(object);
		spin_unlock_irqrestore(&engine->lock, engctx->save);
	}
}