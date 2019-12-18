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
struct drm_mm_node {int allocated; int /*<<< orphan*/  color; int /*<<< orphan*/  size; int /*<<< orphan*/  start; int /*<<< orphan*/  mm; int /*<<< orphan*/  hole_follows; int /*<<< orphan*/  hole_stack; int /*<<< orphan*/  node_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void drm_mm_replace_node(struct drm_mm_node *old, struct drm_mm_node *new)
{
	list_replace(&old->node_list, &new->node_list);
	list_replace(&old->hole_stack, &new->hole_stack);
	new->hole_follows = old->hole_follows;
	new->mm = old->mm;
	new->start = old->start;
	new->size = old->size;
	new->color = old->color;

	old->allocated = 0;
	new->allocated = 1;
}