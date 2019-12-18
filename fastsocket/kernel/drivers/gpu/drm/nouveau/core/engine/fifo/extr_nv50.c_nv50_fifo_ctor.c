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
struct nv50_fifo_priv {int /*<<< orphan*/ * playlist; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sclass; int /*<<< orphan*/ * cclass; } ;
struct TYPE_3__ {int unit; int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int nouveau_fifo_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int,int,struct nv50_fifo_priv**) ; 
 int nouveau_gpuobj_new (struct nouveau_object*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv04_fifo_intr ; 
 int /*<<< orphan*/  nv50_fifo_cclass ; 
 int /*<<< orphan*/  nv50_fifo_sclass ; 
 TYPE_2__* nv_engine (struct nv50_fifo_priv*) ; 
 struct nouveau_object* nv_object (struct nv50_fifo_priv*) ; 
 TYPE_1__* nv_subdev (struct nv50_fifo_priv*) ; 

__attribute__((used)) static int
nv50_fifo_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nv50_fifo_priv *priv;
	int ret;

	ret = nouveau_fifo_create(parent, engine, oclass, 1, 127, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	ret = nouveau_gpuobj_new(parent, NULL, 128 * 4, 0x1000, 0,
				&priv->playlist[0]);
	if (ret)
		return ret;

	ret = nouveau_gpuobj_new(parent, NULL, 128 * 4, 0x1000, 0,
				&priv->playlist[1]);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00000100;
	nv_subdev(priv)->intr = nv04_fifo_intr;
	nv_engine(priv)->cclass = &nv50_fifo_cclass;
	nv_engine(priv)->sclass = nv50_fifo_sclass;
	return 0;
}