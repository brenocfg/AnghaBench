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
struct nv04_instobj_priv {int /*<<< orphan*/  base; int /*<<< orphan*/  mem; } ;
struct nv04_instmem_priv {int /*<<< orphan*/  heap; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_instobj_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_mm_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv04_instobj_dtor(struct nouveau_object *object)
{
	struct nv04_instmem_priv *priv = (void *)object->engine;
	struct nv04_instobj_priv *node = (void *)object;
	nouveau_mm_free(&priv->heap, &node->mem);
	nouveau_instobj_destroy(&node->base);
}