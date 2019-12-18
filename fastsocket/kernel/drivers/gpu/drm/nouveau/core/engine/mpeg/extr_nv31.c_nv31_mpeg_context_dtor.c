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
struct nv31_mpeg_priv {int /*<<< orphan*/  refcount; } ;
struct nv31_mpeg_chan {int /*<<< orphan*/  base; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_object_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv31_mpeg_context_dtor(struct nouveau_object *object)
{
	struct nv31_mpeg_priv *priv = (void *)object->engine;
	struct nv31_mpeg_chan *chan = (void *)object;
	atomic_dec(&priv->refcount);
	nouveau_object_destroy(&chan->base);
}