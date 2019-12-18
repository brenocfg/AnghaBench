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
struct nve0_copy_priv {int dummy; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sclass; int /*<<< orphan*/ * cclass; } ;
struct TYPE_3__ {int unit; } ;

/* Variables and functions */
 int ENODEV ; 
 int nouveau_engine_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int,char*,char*,struct nve0_copy_priv**) ; 
 TYPE_2__* nv_engine (struct nve0_copy_priv*) ; 
 struct nouveau_object* nv_object (struct nve0_copy_priv*) ; 
 int nv_rd32 (struct nouveau_object*,int) ; 
 TYPE_1__* nv_subdev (struct nve0_copy_priv*) ; 
 int /*<<< orphan*/  nve0_copy_cclass ; 
 int /*<<< orphan*/  nve0_copy_sclass ; 

__attribute__((used)) static int
nve0_copy0_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nve0_copy_priv *priv;
	int ret;

	if (nv_rd32(parent, 0x022500) & 0x00000100)
		return -ENODEV;

	ret = nouveau_engine_create(parent, engine, oclass, true,
				    "PCE0", "copy0", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00000040;
	nv_engine(priv)->cclass = &nve0_copy_cclass;
	nv_engine(priv)->sclass = nve0_copy_sclass;
	return 0;
}