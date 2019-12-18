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
struct nvc0_graph_priv {int firmware; int rop_nr; int gpc_nr; int* tpc_nr; int tpc_total; int magic_not_rop_nr; int /*<<< orphan*/  unk4188b8; int /*<<< orphan*/  unk4188b4; int /*<<< orphan*/  fuc41ad; int /*<<< orphan*/  fuc41ac; int /*<<< orphan*/  fuc409d; int /*<<< orphan*/  fuc409c; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int firmware; int rop_nr; int gpc_nr; int* tpc_nr; int tpc_total; int magic_not_rop_nr; int /*<<< orphan*/  unk4188b8; int /*<<< orphan*/  unk4188b4; int /*<<< orphan*/  fuc41ad; int /*<<< orphan*/  fuc41ac; int /*<<< orphan*/  fuc409d; int /*<<< orphan*/  fuc409c; } ;
struct nouveau_device {int chipset; int /*<<< orphan*/  cfgopt; } ;
struct TYPE_4__ {int /*<<< orphan*/  sclass; int /*<<< orphan*/ * cclass; } ;
struct TYPE_3__ {int unit; int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int EINVAL ; 
 int GPC_UNIT (int,int) ; 
 scalar_t__ nouveau_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 int nouveau_gpuobj_new (struct nvc0_graph_priv*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nouveau_graph_create (struct nvc0_graph_priv*,struct nvc0_graph_priv*,struct nouveau_oclass*,int,struct nvc0_graph_priv**) ; 
 struct nouveau_device* nv_device (struct nvc0_graph_priv*) ; 
 TYPE_2__* nv_engine (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nv_info (struct nvc0_graph_priv*,char*) ; 
 struct nvc0_graph_priv* nv_object (struct nvc0_graph_priv*) ; 
 int nv_rd32 (struct nvc0_graph_priv*,int) ; 
 TYPE_1__* nv_subdev (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvc0_graph_cclass ; 
 int nvc0_graph_class (struct nvc0_graph_priv*) ; 
 scalar_t__ nvc0_graph_ctor_fw (struct nvc0_graph_priv*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvc0_graph_intr ; 
 int /*<<< orphan*/  nvc0_graph_sclass ; 
 int /*<<< orphan*/  nvc1_graph_sclass ; 
 int /*<<< orphan*/  nvc8_graph_sclass ; 

__attribute__((used)) static int
nvc0_graph_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nouveau_device *device = nv_device(parent);
	struct nvc0_graph_priv *priv;
	int ret, i;

	ret = nouveau_graph_create(parent, engine, oclass, true, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x18001000;
	nv_subdev(priv)->intr = nvc0_graph_intr;
	nv_engine(priv)->cclass = &nvc0_graph_cclass;

	if (nouveau_boolopt(device->cfgopt, "NvGrUseFW", false)) {
		nv_info(priv, "using external firmware\n");
		if (nvc0_graph_ctor_fw(priv, "fuc409c", &priv->fuc409c) ||
		    nvc0_graph_ctor_fw(priv, "fuc409d", &priv->fuc409d) ||
		    nvc0_graph_ctor_fw(priv, "fuc41ac", &priv->fuc41ac) ||
		    nvc0_graph_ctor_fw(priv, "fuc41ad", &priv->fuc41ad))
			return -EINVAL;
		priv->firmware = true;
	}

	switch (nvc0_graph_class(priv)) {
	case 0x9097:
		nv_engine(priv)->sclass = nvc0_graph_sclass;
		break;
	case 0x9197:
		nv_engine(priv)->sclass = nvc1_graph_sclass;
		break;
	case 0x9297:
		nv_engine(priv)->sclass = nvc8_graph_sclass;
		break;
	}

	ret = nouveau_gpuobj_new(parent, NULL, 0x1000, 256, 0, &priv->unk4188b4);
	if (ret)
		return ret;

	ret = nouveau_gpuobj_new(parent, NULL, 0x1000, 256, 0, &priv->unk4188b8);
	if (ret)
		return ret;

	for (i = 0; i < 0x1000; i += 4) {
		nv_wo32(priv->unk4188b4, i, 0x00000010);
		nv_wo32(priv->unk4188b8, i, 0x00000010);
	}

	priv->rop_nr = (nv_rd32(priv, 0x409604) & 0x001f0000) >> 16;
	priv->gpc_nr =  nv_rd32(priv, 0x409604) & 0x0000001f;
	for (i = 0; i < priv->gpc_nr; i++) {
		priv->tpc_nr[i]  = nv_rd32(priv, GPC_UNIT(i, 0x2608));
		priv->tpc_total += priv->tpc_nr[i];
	}

	/*XXX: these need figuring out... though it might not even matter */
	switch (nv_device(priv)->chipset) {
	case 0xc0:
		if (priv->tpc_total == 11) { /* 465, 3/4/4/0, 4 */
			priv->magic_not_rop_nr = 0x07;
		} else
		if (priv->tpc_total == 14) { /* 470, 3/3/4/4, 5 */
			priv->magic_not_rop_nr = 0x05;
		} else
		if (priv->tpc_total == 15) { /* 480, 3/4/4/4, 6 */
			priv->magic_not_rop_nr = 0x06;
		}
		break;
	case 0xc3: /* 450, 4/0/0/0, 2 */
		priv->magic_not_rop_nr = 0x03;
		break;
	case 0xc4: /* 460, 3/4/0/0, 4 */
		priv->magic_not_rop_nr = 0x01;
		break;
	case 0xc1: /* 2/0/0/0, 1 */
		priv->magic_not_rop_nr = 0x01;
		break;
	case 0xc8: /* 4/4/3/4, 5 */
		priv->magic_not_rop_nr = 0x06;
		break;
	case 0xce: /* 4/4/0/0, 4 */
		priv->magic_not_rop_nr = 0x03;
		break;
	case 0xcf: /* 4/0/0/0, 3 */
		priv->magic_not_rop_nr = 0x03;
		break;
	case 0xd9: /* 1/0/0/0, 1 */
		priv->magic_not_rop_nr = 0x01;
		break;
	}

	return 0;
}