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
struct nv50_instobj_priv {int /*<<< orphan*/  base; int /*<<< orphan*/  mem; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* put ) (struct nouveau_fb*,int /*<<< orphan*/ *) ;} ;
struct nouveau_fb {TYPE_1__ ram; } ;

/* Variables and functions */
 struct nouveau_fb* nouveau_fb (struct nouveau_object*) ; 
 int /*<<< orphan*/  nouveau_instobj_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_fb*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv50_instobj_dtor(struct nouveau_object *object)
{
	struct nv50_instobj_priv *node = (void *)object;
	struct nouveau_fb *pfb = nouveau_fb(object);
	pfb->ram.put(pfb, &node->mem);
	nouveau_instobj_destroy(&node->base);
}