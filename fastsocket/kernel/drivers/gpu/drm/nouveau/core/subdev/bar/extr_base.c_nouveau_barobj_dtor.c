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
struct nouveau_object {scalar_t__ engine; } ;
struct TYPE_2__ {scalar_t__ node; } ;
struct nouveau_barobj {int /*<<< orphan*/  base; TYPE_1__ vma; } ;
struct nouveau_bar {int /*<<< orphan*/  (* unmap ) (struct nouveau_bar*,TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_object_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_bar*,TYPE_1__*) ; 

__attribute__((used)) static void
nouveau_barobj_dtor(struct nouveau_object *object)
{
	struct nouveau_bar *bar = (void *)object->engine;
	struct nouveau_barobj *barobj = (void *)object;
	if (barobj->vma.node)
		bar->unmap(bar, &barobj->vma);
	nouveau_object_destroy(&barobj->base);
}