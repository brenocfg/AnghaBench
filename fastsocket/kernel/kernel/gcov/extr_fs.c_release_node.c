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
struct gcov_node {scalar_t__ ghost; int /*<<< orphan*/  dentry; int /*<<< orphan*/  all; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcov_info_free (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct gcov_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_links (struct gcov_node*) ; 

__attribute__((used)) static void release_node(struct gcov_node *node)
{
	list_del(&node->list);
	list_del(&node->all);
	debugfs_remove(node->dentry);
	remove_links(node);
	if (node->ghost)
		gcov_info_free(node->ghost);
	kfree(node);
}