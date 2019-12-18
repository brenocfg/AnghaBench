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
struct nv40_graph_priv {int dummy; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tile_prog; int /*<<< orphan*/  sclass; int /*<<< orphan*/ * cclass; } ;
struct TYPE_3__ {int unit; int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int nouveau_graph_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int,struct nv40_graph_priv**) ; 
 int /*<<< orphan*/  nv40_graph_cclass ; 
 int /*<<< orphan*/  nv40_graph_intr ; 
 int /*<<< orphan*/  nv40_graph_sclass ; 
 int /*<<< orphan*/  nv40_graph_tile_prog ; 
 scalar_t__ nv44_graph_class (struct nv40_graph_priv*) ; 
 int /*<<< orphan*/  nv44_graph_sclass ; 
 TYPE_2__* nv_engine (struct nv40_graph_priv*) ; 
 struct nouveau_object* nv_object (struct nv40_graph_priv*) ; 
 TYPE_1__* nv_subdev (struct nv40_graph_priv*) ; 

__attribute__((used)) static int
nv40_graph_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nv40_graph_priv *priv;
	int ret;

	ret = nouveau_graph_create(parent, engine, oclass, true, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->unit = 0x00001000;
	nv_subdev(priv)->intr = nv40_graph_intr;
	nv_engine(priv)->cclass = &nv40_graph_cclass;
	if (nv44_graph_class(priv))
		nv_engine(priv)->sclass = nv44_graph_sclass;
	else
		nv_engine(priv)->sclass = nv40_graph_sclass;
	nv_engine(priv)->tile_prog = nv40_graph_tile_prog;
	return 0;
}