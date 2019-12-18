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
typedef  int u64 ;
struct nouveau_vma {TYPE_1__* node; } ;
struct TYPE_2__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_vm_unmap_at (struct nouveau_vma*,int /*<<< orphan*/ ,int) ; 

void
nouveau_vm_unmap(struct nouveau_vma *vma)
{
	nouveau_vm_unmap_at(vma, 0, (u64)vma->node->length << 12);
}