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
struct drm_mm_node {int /*<<< orphan*/  node_list; } ;
struct drm_mm {int num_unused; int /*<<< orphan*/  unused_lock; int /*<<< orphan*/  unused_nodes; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MM_UNUSED_TARGET ; 
 struct drm_mm_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int drm_mm_pre_get(struct drm_mm *mm)
{
	struct drm_mm_node *node;

	spin_lock(&mm->unused_lock);
	while (mm->num_unused < MM_UNUSED_TARGET) {
		spin_unlock(&mm->unused_lock);
		node = kzalloc(sizeof(*node), GFP_KERNEL);
		spin_lock(&mm->unused_lock);

		if (unlikely(node == NULL)) {
			int ret = (mm->num_unused < 2) ? -ENOMEM : 0;
			spin_unlock(&mm->unused_lock);
			return ret;
		}
		++mm->num_unused;
		list_add_tail(&node->node_list, &mm->unused_nodes);
	}
	spin_unlock(&mm->unused_lock);
	return 0;
}