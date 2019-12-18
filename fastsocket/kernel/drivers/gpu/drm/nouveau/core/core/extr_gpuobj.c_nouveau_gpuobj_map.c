#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_vma {int dummy; } ;
struct nouveau_mem {int dummy; } ;
struct nouveau_instobj {int dummy; } ;
struct nouveau_gpuobj {int dummy; } ;
struct nouveau_bar {int (* umap ) (struct nouveau_bar*,struct nouveau_mem*,int /*<<< orphan*/ ,struct nouveau_vma*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NV_MEMOBJ_CLASS ; 
 struct nouveau_bar* nouveau_bar (struct nouveau_gpuobj*) ; 
 int /*<<< orphan*/  nv_object (struct nouveau_gpuobj*) ; 
 scalar_t__ nv_pclass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct nouveau_bar*,struct nouveau_mem*,int /*<<< orphan*/ ,struct nouveau_vma*) ; 

int
nouveau_gpuobj_map(struct nouveau_gpuobj *gpuobj, u32 access,
		   struct nouveau_vma *vma)
{
	struct nouveau_bar *bar = nouveau_bar(gpuobj);
	int ret = -EINVAL;

	if (bar && bar->umap) {
		struct nouveau_instobj *iobj = (void *)
			nv_pclass(nv_object(gpuobj), NV_MEMOBJ_CLASS);
		struct nouveau_mem **mem = (void *)(iobj + 1);
		ret = bar->umap(bar, *mem, access, vma);
	}

	return ret;
}