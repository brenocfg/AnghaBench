#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {TYPE_2__* uevent; } ;
struct TYPE_6__ {int /*<<< orphan*/  bar; int /*<<< orphan*/  mem; } ;
struct nve0_fifo_priv {TYPE_3__ base; TYPE_1__ user; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  sclass; int /*<<< orphan*/ * cclass; } ;
struct TYPE_9__ {int unit; int /*<<< orphan*/  intr; } ;
struct TYPE_7__ {struct nve0_fifo_priv* priv; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVOBJ_FLAG_ZERO_ALLOC ; 
 int /*<<< orphan*/  NV_MEM_ACCESS_RW ; 
 int nouveau_fifo_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,int,struct nve0_fifo_priv**) ; 
 int nouveau_gpuobj_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nouveau_gpuobj_new (struct nouveau_object*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* nv_engine (struct nve0_fifo_priv*) ; 
 struct nouveau_object* nv_object (struct nve0_fifo_priv*) ; 
 TYPE_4__* nv_subdev (struct nve0_fifo_priv*) ; 
 int /*<<< orphan*/  nve0_fifo_cclass ; 
 int /*<<< orphan*/  nve0_fifo_intr ; 
 int /*<<< orphan*/  nve0_fifo_sclass ; 
 int /*<<< orphan*/  nve0_fifo_uevent_disable ; 
 int /*<<< orphan*/  nve0_fifo_uevent_enable ; 

__attribute__((used)) static int
nve0_fifo_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nve0_fifo_priv *priv;
	int ret;

	ret = nouveau_fifo_create(parent, engine, oclass, 0, 4095, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	ret = nouveau_gpuobj_new(parent, NULL, 4096 * 0x200, 0x1000,
				 NVOBJ_FLAG_ZERO_ALLOC, &priv->user.mem);
	if (ret)
		return ret;

	ret = nouveau_gpuobj_map(priv->user.mem, NV_MEM_ACCESS_RW,
				&priv->user.bar);
	if (ret)
		return ret;

	priv->base.uevent->enable = nve0_fifo_uevent_enable;
	priv->base.uevent->disable = nve0_fifo_uevent_disable;
	priv->base.uevent->priv = priv;

	nv_subdev(priv)->unit = 0x00000100;
	nv_subdev(priv)->intr = nve0_fifo_intr;
	nv_engine(priv)->cclass = &nve0_fifo_cclass;
	nv_engine(priv)->sclass = nve0_fifo_sclass;
	return 0;
}