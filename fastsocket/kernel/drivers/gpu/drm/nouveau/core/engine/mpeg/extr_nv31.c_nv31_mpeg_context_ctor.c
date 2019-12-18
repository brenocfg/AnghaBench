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
typedef  int /*<<< orphan*/  u32 ;
struct nv31_mpeg_priv {int /*<<< orphan*/  refcount; } ;
struct nv31_mpeg_chan {int dummy; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 int nouveau_object_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,struct nv31_mpeg_chan**) ; 
 struct nouveau_object* nv_object (struct nv31_mpeg_chan*) ; 

__attribute__((used)) static int
nv31_mpeg_context_ctor(struct nouveau_object *parent,
		       struct nouveau_object *engine,
		       struct nouveau_oclass *oclass, void *data, u32 size,
		       struct nouveau_object **pobject)
{
	struct nv31_mpeg_priv *priv = (void *)engine;
	struct nv31_mpeg_chan *chan;
	int ret;

	if (!atomic_add_unless(&priv->refcount, 1, 1))
		return -EBUSY;

	ret = nouveau_object_create(parent, engine, oclass, 0, &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	return 0;
}