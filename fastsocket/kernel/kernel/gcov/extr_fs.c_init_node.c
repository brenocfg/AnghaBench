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
struct gcov_node {int /*<<< orphan*/  name; struct gcov_node* parent; struct gcov_info* info; int /*<<< orphan*/  all; int /*<<< orphan*/  children; int /*<<< orphan*/  list; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void init_node(struct gcov_node *node, struct gcov_info *info,
		      const char *name, struct gcov_node *parent)
{
	INIT_LIST_HEAD(&node->list);
	INIT_LIST_HEAD(&node->children);
	INIT_LIST_HEAD(&node->all);
	node->info = info;
	node->parent = parent;
	if (name)
		strcpy(node->name, name);
}