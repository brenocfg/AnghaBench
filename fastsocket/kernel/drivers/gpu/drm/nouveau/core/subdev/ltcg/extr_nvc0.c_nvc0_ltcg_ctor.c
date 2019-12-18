#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvc0_ltcg_priv {int subp_nr; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int nouveau_ltcg_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,struct nvc0_ltcg_priv**) ; 
 int /*<<< orphan*/  nv_mask (struct nvc0_ltcg_priv*,int,int,int) ; 
 struct nouveau_object* nv_object (struct nvc0_ltcg_priv*) ; 
 int nv_rd32 (struct nvc0_ltcg_priv*,int) ; 
 TYPE_1__* nv_subdev (struct nvc0_ltcg_priv*) ; 
 int /*<<< orphan*/  nvc0_ltcg_intr ; 

__attribute__((used)) static int
nvc0_ltcg_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nvc0_ltcg_priv *priv;
	int ret;

	ret = nouveau_ltcg_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->subp_nr = nv_rd32(priv, 0x17e8dc) >> 24;
	nv_mask(priv, 0x17e820, 0x00100000, 0x00000000); /* INTR_EN &= ~0x10 */

	nv_subdev(priv)->intr = nvc0_ltcg_intr;
	return 0;
}