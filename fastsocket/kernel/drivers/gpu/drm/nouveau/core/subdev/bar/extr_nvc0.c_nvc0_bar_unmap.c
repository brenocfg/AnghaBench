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
struct nvc0_bar_priv {TYPE_2__* bar; } ;
struct nouveau_vma {scalar_t__ vm; } ;
struct nouveau_bar {int dummy; } ;
struct TYPE_4__ {scalar_t__ vm; TYPE_1__* pgd; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_vm_put (struct nouveau_vma*) ; 
 int /*<<< orphan*/  nouveau_vm_unmap (struct nouveau_vma*) ; 
 int /*<<< orphan*/  nv_subdev (struct nouveau_bar*) ; 
 int /*<<< orphan*/  nvc0_vm_flush_engine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nvc0_bar_unmap(struct nouveau_bar *bar, struct nouveau_vma *vma)
{
	struct nvc0_bar_priv *priv = (void *)bar;
	int i = !(vma->vm == priv->bar[0].vm);

	nouveau_vm_unmap(vma);
	nvc0_vm_flush_engine(nv_subdev(bar), priv->bar[i].pgd->addr, 5);
	nouveau_vm_put(vma);
}