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
typedef  int /*<<< orphan*/  u32 ;
struct nv04_instmem_priv {int /*<<< orphan*/  ramfc; int /*<<< orphan*/  ramro; int /*<<< orphan*/  ramht; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; int /*<<< orphan*/  pause; } ;
struct nv04_fifo_priv {int /*<<< orphan*/  ramfc_desc; TYPE_1__ base; int /*<<< orphan*/  ramfc; int /*<<< orphan*/  ramro; int /*<<< orphan*/  ramht; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sclass; int /*<<< orphan*/ * cclass; } ;
struct TYPE_5__ {int unit; int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int nouveau_fifo_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,int,struct nv04_fifo_priv**) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_ramht_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv04_fifo_intr ; 
 int /*<<< orphan*/  nv04_fifo_pause ; 
 int /*<<< orphan*/  nv04_fifo_start ; 
 struct nv04_instmem_priv* nv04_instmem (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv10_fifo_cclass ; 
 int /*<<< orphan*/  nv10_fifo_sclass ; 
 int /*<<< orphan*/  nv10_ramfc ; 
 TYPE_3__* nv_engine (struct nv04_fifo_priv*) ; 
 struct nouveau_object* nv_object (struct nv04_fifo_priv*) ; 
 TYPE_2__* nv_subdev (struct nv04_fifo_priv*) ; 

__attribute__((used)) static int
nv10_fifo_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nv04_instmem_priv *imem = nv04_instmem(parent);
	struct nv04_fifo_priv *priv;
	int ret;

	ret = nouveau_fifo_create(parent, engine, oclass, 0, 31, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nouveau_ramht_ref(imem->ramht, &priv->ramht);
	nouveau_gpuobj_ref(imem->ramro, &priv->ramro);
	nouveau_gpuobj_ref(imem->ramfc, &priv->ramfc);

	nv_subdev(priv)->unit = 0x00000100;
	nv_subdev(priv)->intr = nv04_fifo_intr;
	nv_engine(priv)->cclass = &nv10_fifo_cclass;
	nv_engine(priv)->sclass = nv10_fifo_sclass;
	priv->base.pause = nv04_fifo_pause;
	priv->base.start = nv04_fifo_start;
	priv->ramfc_desc = nv10_ramfc;
	return 0;
}