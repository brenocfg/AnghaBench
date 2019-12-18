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
struct TYPE_8__ {int nr; int /*<<< orphan*/ * dp; int /*<<< orphan*/  hdmi; int /*<<< orphan*/  hda_eld; int /*<<< orphan*/  power; } ;
struct TYPE_7__ {int nr; int /*<<< orphan*/  sense; int /*<<< orphan*/  power; } ;
struct TYPE_6__ {int nr; } ;
struct nv50_disp_priv {TYPE_3__ sor; TYPE_2__ dac; TYPE_1__ head; int /*<<< orphan*/  sclass; int /*<<< orphan*/  supervisor; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/ * cclass; int /*<<< orphan*/  sclass; } ;
struct TYPE_9__ {int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nouveau_disp_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int,char*,char*,struct nv50_disp_priv**) ; 
 int /*<<< orphan*/  nv50_dac_power ; 
 int /*<<< orphan*/  nv50_dac_sense ; 
 int /*<<< orphan*/  nv50_disp_cclass ; 
 int /*<<< orphan*/  nv50_sor_power ; 
 TYPE_5__* nv_engine (struct nv50_disp_priv*) ; 
 struct nouveau_object* nv_object (struct nv50_disp_priv*) ; 
 int nv_rd32 (struct nouveau_object*,int) ; 
 TYPE_4__* nv_subdev (struct nv50_disp_priv*) ; 
 int /*<<< orphan*/  nvd0_disp_base_oclass ; 
 int /*<<< orphan*/  nvd0_disp_intr ; 
 int /*<<< orphan*/  nvd0_disp_intr_supervisor ; 
 int /*<<< orphan*/  nvd0_disp_sclass ; 
 int /*<<< orphan*/  nvd0_hda_eld ; 
 int /*<<< orphan*/  nvd0_hdmi_ctrl ; 
 int /*<<< orphan*/  nvd0_sor_dp_func ; 

__attribute__((used)) static int
nvd0_disp_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nv50_disp_priv *priv;
	int heads = nv_rd32(parent, 0x022448);
	int ret;

	ret = nouveau_disp_create(parent, engine, oclass, heads,
				  "PDISP", "display", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_engine(priv)->sclass = nvd0_disp_base_oclass;
	nv_engine(priv)->cclass = &nv50_disp_cclass;
	nv_subdev(priv)->intr = nvd0_disp_intr;
	INIT_WORK(&priv->supervisor, nvd0_disp_intr_supervisor);
	priv->sclass = nvd0_disp_sclass;
	priv->head.nr = heads;
	priv->dac.nr = 3;
	priv->sor.nr = 4;
	priv->dac.power = nv50_dac_power;
	priv->dac.sense = nv50_dac_sense;
	priv->sor.power = nv50_sor_power;
	priv->sor.hda_eld = nvd0_hda_eld;
	priv->sor.hdmi = nvd0_hdmi_ctrl;
	priv->sor.dp = &nvd0_sor_dp_func;
	return 0;
}