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
struct drm_mm_node {int /*<<< orphan*/  node_list; struct drm_mm* mm; } ;
struct drm_mm {scalar_t__ num_unused; int /*<<< orphan*/  unused_lock; int /*<<< orphan*/  unused_nodes; } ;

/* Variables and functions */
 scalar_t__ MM_UNUSED_TARGET ; 
 int /*<<< orphan*/  drm_mm_remove_node (struct drm_mm_node*) ; 
 int /*<<< orphan*/  kfree (struct drm_mm_node*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void drm_mm_put_block(struct drm_mm_node *node)
{

	struct drm_mm *mm = node->mm;

	drm_mm_remove_node(node);

	spin_lock(&mm->unused_lock);
	if (mm->num_unused < MM_UNUSED_TARGET) {
		list_add(&node->node_list, &mm->unused_nodes);
		++mm->num_unused;
	} else
		kfree(node);
	spin_unlock(&mm->unused_lock);
}