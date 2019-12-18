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
struct TYPE_2__ {int /*<<< orphan*/  pll_calc; int /*<<< orphan*/  pll_set; } ;
struct nvc0_clock_priv {TYPE_1__ base; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_clock_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,struct nvc0_clock_priv**) ; 
 struct nouveau_object* nv_object (struct nvc0_clock_priv*) ; 
 int /*<<< orphan*/  nva3_clock_pll_calc ; 
 int /*<<< orphan*/  nvc0_clock_pll_set ; 

__attribute__((used)) static int
nvc0_clock_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nvc0_clock_priv *priv;
	int ret;

	ret = nouveau_clock_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.pll_set = nvc0_clock_pll_set;
	priv->base.pll_calc = nva3_clock_pll_calc;
	return 0;
}