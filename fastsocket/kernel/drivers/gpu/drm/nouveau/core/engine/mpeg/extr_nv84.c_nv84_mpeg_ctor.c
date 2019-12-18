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
struct nv84_mpeg_priv {int dummy; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tlb_flush; int /*<<< orphan*/  sclass; int /*<<< orphan*/ * cclass; } ;
struct TYPE_3__ {int unit; int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int nouveau_mpeg_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,struct nv84_mpeg_priv**) ; 
 int /*<<< orphan*/  nv50_mpeg_intr ; 
 int /*<<< orphan*/  nv50_mpeg_tlb_flush ; 
 int /*<<< orphan*/  nv84_mpeg_cclass ; 
 int /*<<< orphan*/  nv84_mpeg_sclass ; 
 TYPE_2__* nv_engine (struct nv84_mpeg_priv*) ; 
 struct nouveau_object* nv_object (struct nv84_mpeg_priv*) ; 
 TYPE_1__* nv_subdev (struct nv84_mpeg_priv*) ; 

__attribute__((used)) static int
nv84_mpeg_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nv84_mpeg_priv *priv;
	int ret;

	ret = nouveau_mpeg_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00000002;
	nv_subdev(priv)->intr = nv50_mpeg_intr;
	nv_engine(priv)->cclass = &nv84_mpeg_cclass;
	nv_engine(priv)->sclass = nv84_mpeg_sclass;
	nv_engine(priv)->tlb_flush = nv50_mpeg_tlb_flush;
	return 0;
}