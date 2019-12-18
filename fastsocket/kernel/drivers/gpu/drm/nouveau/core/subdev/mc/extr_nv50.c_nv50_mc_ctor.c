#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  intr_map; } ;
struct nv50_mc_priv {TYPE_1__ base; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int nouveau_mc_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,struct nv50_mc_priv**) ; 
 int /*<<< orphan*/  nouveau_mc_intr ; 
 int /*<<< orphan*/  nv50_mc_intr ; 
 struct nouveau_object* nv_object (struct nv50_mc_priv*) ; 
 TYPE_2__* nv_subdev (struct nv50_mc_priv*) ; 

__attribute__((used)) static int
nv50_mc_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv50_mc_priv *priv;
	int ret;

	ret = nouveau_mc_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->intr = nouveau_mc_intr;
	priv->base.intr_map = nv50_mc_intr;
	return 0;
}