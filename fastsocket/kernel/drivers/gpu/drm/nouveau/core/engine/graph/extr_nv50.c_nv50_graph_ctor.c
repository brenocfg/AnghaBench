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
struct nv50_graph_priv {int /*<<< orphan*/  lock; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_6__ {int chipset; } ;
struct TYPE_5__ {int /*<<< orphan*/  tlb_flush; int /*<<< orphan*/  sclass; int /*<<< orphan*/ * cclass; } ;
struct TYPE_4__ {int unit; int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int nouveau_graph_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int,struct nv50_graph_priv**) ; 
 int /*<<< orphan*/  nv50_graph_cclass ; 
 int /*<<< orphan*/  nv50_graph_intr ; 
 int /*<<< orphan*/  nv50_graph_sclass ; 
 int /*<<< orphan*/  nv50_graph_tlb_flush ; 
 int /*<<< orphan*/  nv84_graph_sclass ; 
 int /*<<< orphan*/  nv84_graph_tlb_flush ; 
 TYPE_3__* nv_device (struct nv50_graph_priv*) ; 
 TYPE_2__* nv_engine (struct nv50_graph_priv*) ; 
 struct nouveau_object* nv_object (struct nv50_graph_priv*) ; 
 TYPE_1__* nv_subdev (struct nv50_graph_priv*) ; 
 int /*<<< orphan*/  nva0_graph_sclass ; 
 int /*<<< orphan*/  nva3_graph_sclass ; 
 int /*<<< orphan*/  nvaf_graph_sclass ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nv50_graph_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nv50_graph_priv *priv;
	int ret;

	ret = nouveau_graph_create(parent, engine, oclass, true, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00201000;
	nv_subdev(priv)->intr = nv50_graph_intr;
	nv_engine(priv)->cclass = &nv50_graph_cclass;

	switch (nv_device(priv)->chipset) {
	case 0x50:
		nv_engine(priv)->sclass = nv50_graph_sclass;
		break;
	case 0x84:
	case 0x86:
	case 0x92:
	case 0x94:
	case 0x96:
	case 0x98:
		nv_engine(priv)->sclass = nv84_graph_sclass;
		break;
	case 0xa0:
	case 0xaa:
	case 0xac:
		nv_engine(priv)->sclass = nva0_graph_sclass;
		break;
	case 0xa3:
	case 0xa5:
	case 0xa8:
		nv_engine(priv)->sclass = nva3_graph_sclass;
		break;
	case 0xaf:
		nv_engine(priv)->sclass = nvaf_graph_sclass;
		break;

	};

	if (nv_device(priv)->chipset == 0x50 ||
	    nv_device(priv)->chipset == 0xac)
		nv_engine(priv)->tlb_flush = nv50_graph_tlb_flush;
	else
		nv_engine(priv)->tlb_flush = nv84_graph_tlb_flush;

	spin_lock_init(&priv->lock);
	return 0;
}