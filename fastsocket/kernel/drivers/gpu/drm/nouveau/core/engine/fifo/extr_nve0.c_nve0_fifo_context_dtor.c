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
struct nve0_fifo_base {int /*<<< orphan*/  base; int /*<<< orphan*/  pgd; int /*<<< orphan*/  vm; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_fifo_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_vm_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nve0_fifo_context_dtor(struct nouveau_object *object)
{
	struct nve0_fifo_base *base = (void *)object;
	nouveau_vm_ref(NULL, &base->vm, base->pgd);
	nouveau_gpuobj_ref(NULL, &base->pgd);
	nouveau_fifo_context_destroy(&base->base);
}