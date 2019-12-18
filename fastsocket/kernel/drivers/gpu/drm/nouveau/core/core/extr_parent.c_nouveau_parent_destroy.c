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
struct nouveau_sclass {struct nouveau_sclass* sclass; } ;
struct nouveau_parent {int /*<<< orphan*/  base; struct nouveau_sclass* sclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nouveau_sclass*) ; 
 int /*<<< orphan*/  nouveau_object_destroy (int /*<<< orphan*/ *) ; 

void
nouveau_parent_destroy(struct nouveau_parent *parent)
{
	struct nouveau_sclass *sclass;

	while ((sclass = parent->sclass)) {
		parent->sclass = sclass->sclass;
		kfree(sclass);
	}

	nouveau_object_destroy(&parent->base);
}