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
struct nvc0_bar_priv {TYPE_2__* bar; } ;
struct nouveau_vma {int dummy; } ;
struct nouveau_mem {int size; } ;
struct nouveau_bar {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pgd; int /*<<< orphan*/  vm; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int nouveau_vm_get (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct nouveau_vma*) ; 
 int /*<<< orphan*/  nouveau_vm_map (struct nouveau_vma*,struct nouveau_mem*) ; 
 int /*<<< orphan*/  nv_subdev (struct nouveau_bar*) ; 
 int /*<<< orphan*/  nvc0_vm_flush_engine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nvc0_bar_kmap(struct nouveau_bar *bar, struct nouveau_mem *mem,
	      u32 flags, struct nouveau_vma *vma)
{
	struct nvc0_bar_priv *priv = (void *)bar;
	int ret;

	ret = nouveau_vm_get(priv->bar[0].vm, mem->size << 12, 12, flags, vma);
	if (ret)
		return ret;

	nouveau_vm_map(vma, mem);
	nvc0_vm_flush_engine(nv_subdev(bar), priv->bar[0].pgd->addr, 5);
	return 0;
}