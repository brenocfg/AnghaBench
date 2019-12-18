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
struct TYPE_2__ {int reserved; int /*<<< orphan*/  alloc; } ;
struct nv04_instmem_priv {int created; int /*<<< orphan*/  ramro; int /*<<< orphan*/  ramfc; int /*<<< orphan*/  ramht; int /*<<< orphan*/  vbios; TYPE_1__ base; int /*<<< orphan*/  heap; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVOBJ_FLAG_ZERO_ALLOC ; 
 int nouveau_gpuobj_new (struct nouveau_object*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nouveau_instmem_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,struct nv04_instmem_priv**) ; 
 int nouveau_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int nouveau_ramht_new (struct nouveau_object*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv04_instmem_alloc ; 
 struct nouveau_object* nv_object (struct nv04_instmem_priv*) ; 

__attribute__((used)) static int
nv04_instmem_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		  struct nouveau_oclass *oclass, void *data, u32 size,
		  struct nouveau_object **pobject)
{
	struct nv04_instmem_priv *priv;
	int ret;

	ret = nouveau_instmem_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	/* PRAMIN aperture maps over the end of VRAM, reserve it */
	priv->base.reserved = 512 * 1024;
	priv->base.alloc    = nv04_instmem_alloc;

	ret = nouveau_mm_init(&priv->heap, 0, priv->base.reserved, 1);
	if (ret)
		return ret;

	/* 0x00000-0x10000: reserve for probable vbios image */
	ret = nouveau_gpuobj_new(parent, NULL, 0x10000, 0, 0, &priv->vbios);
	if (ret)
		return ret;

	/* 0x10000-0x18000: reserve for RAMHT */
	ret = nouveau_ramht_new(parent, NULL, 0x08000, 0, &priv->ramht);
	if (ret)
		return ret;

	/* 0x18000-0x18800: reserve for RAMFC (enough for 32 nv30 channels) */
	ret = nouveau_gpuobj_new(parent, NULL, 0x00800, 0,
				 NVOBJ_FLAG_ZERO_ALLOC, &priv->ramfc);
	if (ret)
		return ret;

	/* 0x18800-0x18a00: reserve for RAMRO */
	ret = nouveau_gpuobj_new(parent, NULL, 0x00200, 0, 0, &priv->ramro);
	if (ret)
		return ret;

	priv->created = true;
	return 0;
}