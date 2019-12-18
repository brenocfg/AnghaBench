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
typedef  int u32 ;
struct nv50_display_ovly_class {scalar_t__ head; int /*<<< orphan*/  pushbuf; } ;
struct TYPE_3__ {scalar_t__ nr; } ;
struct nv50_disp_priv {TYPE_1__ head; } ;
struct nv50_disp_dmac {int dummy; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  object_detach; int /*<<< orphan*/  object_attach; } ;

/* Variables and functions */
 int EINVAL ; 
 int nv50_disp_dmac_create_ (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,scalar_t__,int,void**) ; 
 struct nouveau_object* nv_object (struct nv50_disp_dmac*) ; 
 TYPE_2__* nv_parent (struct nv50_disp_dmac*) ; 
 int /*<<< orphan*/  nvd0_disp_dmac_object_attach ; 
 int /*<<< orphan*/  nvd0_disp_dmac_object_detach ; 

__attribute__((used)) static int
nvd0_disp_ovly_ctor(struct nouveau_object *parent,
		    struct nouveau_object *engine,
		    struct nouveau_oclass *oclass, void *data, u32 size,
		    struct nouveau_object **pobject)
{
	struct nv50_display_ovly_class *args = data;
	struct nv50_disp_priv *priv = (void *)engine;
	struct nv50_disp_dmac *dmac;
	int ret;

	if (size < sizeof(*args) || args->head >= priv->head.nr)
		return -EINVAL;

	ret = nv50_disp_dmac_create_(parent, engine, oclass, args->pushbuf,
				     5 + args->head, sizeof(*dmac),
				     (void **)&dmac);
	*pobject = nv_object(dmac);
	if (ret)
		return ret;

	nv_parent(dmac)->object_attach = nvd0_disp_dmac_object_attach;
	nv_parent(dmac)->object_detach = nvd0_disp_dmac_object_detach;
	return 0;
}