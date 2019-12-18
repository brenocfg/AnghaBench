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
struct gcov_node {int dummy; } ;
struct gcov_info {int /*<<< orphan*/  filename; } ;
typedef  enum gcov_action { ____Placeholder_gcov_action } gcov_action ;

/* Variables and functions */
#define  GCOV_ADD 129 
#define  GCOV_REMOVE 128 
 int /*<<< orphan*/  add_node (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_persist ; 
 struct gcov_node* get_node_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghost_node (struct gcov_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_lock ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_node (struct gcov_node*) ; 
 int /*<<< orphan*/  revive_node (struct gcov_node*,struct gcov_info*) ; 

void gcov_event(enum gcov_action action, struct gcov_info *info)
{
	struct gcov_node *node;

	mutex_lock(&node_lock);
	node = get_node_by_name(info->filename);
	switch (action) {
	case GCOV_ADD:
		/* Add new node or revive ghost. */
		if (!node) {
			add_node(info);
			break;
		}
		if (gcov_persist)
			revive_node(node, info);
		else {
			pr_warning("could not add '%s' (already exists)\n",
				   info->filename);
		}
		break;
	case GCOV_REMOVE:
		/* Remove node or turn into ghost. */
		if (!node) {
			pr_warning("could not remove '%s' (not found)\n",
				   info->filename);
			break;
		}
		if (gcov_persist) {
			if (!ghost_node(node))
				break;
		}
		remove_node(node);
		break;
	}
	mutex_unlock(&node_lock);
}