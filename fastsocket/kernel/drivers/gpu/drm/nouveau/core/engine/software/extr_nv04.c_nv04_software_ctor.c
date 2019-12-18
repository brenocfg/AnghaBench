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
struct nv04_software_priv {int dummy; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sclass; int /*<<< orphan*/ * cclass; } ;
struct TYPE_3__ {int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int nouveau_software_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,struct nv04_software_priv**) ; 
 int /*<<< orphan*/  nv04_software_cclass ; 
 int /*<<< orphan*/  nv04_software_intr ; 
 int /*<<< orphan*/  nv04_software_sclass ; 
 TYPE_2__* nv_engine (struct nv04_software_priv*) ; 
 struct nouveau_object* nv_object (struct nv04_software_priv*) ; 
 TYPE_1__* nv_subdev (struct nv04_software_priv*) ; 

__attribute__((used)) static int
nv04_software_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	      struct nouveau_oclass *oclass, void *data, u32 size,
	      struct nouveau_object **pobject)
{
	struct nv04_software_priv *priv;
	int ret;

	ret = nouveau_software_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_engine(priv)->cclass = &nv04_software_cclass;
	nv_engine(priv)->sclass = nv04_software_sclass;
	nv_subdev(priv)->intr = nv04_software_intr;
	return 0;
}