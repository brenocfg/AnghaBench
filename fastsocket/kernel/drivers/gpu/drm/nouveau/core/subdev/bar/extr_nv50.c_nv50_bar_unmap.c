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
struct nouveau_vma {int dummy; } ;
struct nouveau_bar {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_vm_put (struct nouveau_vma*) ; 
 int /*<<< orphan*/  nouveau_vm_unmap (struct nouveau_vma*) ; 
 int /*<<< orphan*/  nv50_vm_flush_engine (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv_subdev (struct nouveau_bar*) ; 

__attribute__((used)) static void
nv50_bar_unmap(struct nouveau_bar *bar, struct nouveau_vma *vma)
{
	nouveau_vm_unmap(vma);
	nv50_vm_flush_engine(nv_subdev(bar), 6);
	nouveau_vm_put(vma);
}