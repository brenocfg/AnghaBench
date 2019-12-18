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
struct gcov_node {int /*<<< orphan*/  all; int /*<<< orphan*/  children; int /*<<< orphan*/  list; int /*<<< orphan*/  dentry; int /*<<< orphan*/  name; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  add_links (struct gcov_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_head ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct gcov_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deskew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcov_data_fops ; 
 int /*<<< orphan*/  init_node (struct gcov_node*,struct gcov_info*,char const*,struct gcov_node*) ; 
 int /*<<< orphan*/  kfree (struct gcov_node*) ; 
 struct gcov_node* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct gcov_node *new_node(struct gcov_node *parent,
				  struct gcov_info *info, const char *name)
{
	struct gcov_node *node;

	node = kzalloc(sizeof(struct gcov_node) + strlen(name) + 1, GFP_KERNEL);
	if (!node) {
		pr_warning("out of memory\n");
		return NULL;
	}
	init_node(node, info, name, parent);
	/* Differentiate between gcov data file nodes and directory nodes. */
	if (info) {
		node->dentry = debugfs_create_file(deskew(node->name), 0600,
					parent->dentry, node, &gcov_data_fops);
	} else
		node->dentry = debugfs_create_dir(node->name, parent->dentry);
	if (!node->dentry) {
		pr_warning("could not create file\n");
		kfree(node);
		return NULL;
	}
	if (info)
		add_links(node, parent->dentry);
	list_add(&node->list, &parent->children);
	list_add(&node->all, &all_head);

	return node;
}