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
struct nouveau_mem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_vm_map_at (struct nouveau_vma*,int /*<<< orphan*/ ,struct nouveau_mem*) ; 

void
nouveau_vm_map(struct nouveau_vma *vma, struct nouveau_mem *node)
{
	nouveau_vm_map_at(vma, 0, node);
}