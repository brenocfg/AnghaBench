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
struct TYPE_3__ {int /*<<< orphan*/  init; } ;
struct TYPE_4__ {TYPE_1__ ram; int /*<<< orphan*/  memtype_valid; } ;
struct nv04_fb_priv {TYPE_2__ base; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_fb_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,struct nv04_fb_priv**) ; 
 int nouveau_fb_preinit (TYPE_2__*) ; 
 int /*<<< orphan*/  nv04_fb_memtype_valid ; 
 int /*<<< orphan*/  nv04_fb_vram_init ; 
 struct nouveau_object* nv_object (struct nv04_fb_priv*) ; 

__attribute__((used)) static int
nv04_fb_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv04_fb_priv *priv;
	int ret;

	ret = nouveau_fb_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.memtype_valid = nv04_fb_memtype_valid;
	priv->base.ram.init = nv04_fb_vram_init;
	return nouveau_fb_preinit(&priv->base);
}