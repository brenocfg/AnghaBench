#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gcov_node {char* links; } ;
struct dentry {int dummy; } ;
struct TYPE_5__ {scalar_t__ ext; } ;
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char debugfs_create_symlink (int /*<<< orphan*/ ,struct dentry*,char*) ; 
 int /*<<< orphan*/  debugfs_remove (char) ; 
 int /*<<< orphan*/  deskew (char*) ; 
 TYPE_2__* gcov_link ; 
 char* get_link_target (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* get_node_info (struct gcov_node*) ; 
 char* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void add_links(struct gcov_node *node, struct dentry *parent)
{
	char *basename;
	char *target;
	int num;
	int i;

	for (num = 0; gcov_link[num].ext; num++)
		/* Nothing. */;
	node->links = kcalloc(num, sizeof(struct dentry *), GFP_KERNEL);
	if (!node->links)
		return;
	for (i = 0; i < num; i++) {
		target = get_link_target(get_node_info(node)->filename,
					 &gcov_link[i]);
		if (!target)
			goto out_err;
		basename = strrchr(target, '/');
		if (!basename)
			goto out_err;
		basename++;
		node->links[i] = debugfs_create_symlink(deskew(basename),
							parent,	target);
		if (!node->links[i])
			goto out_err;
		kfree(target);
	}

	return;
out_err:
	kfree(target);
	while (i-- > 0)
		debugfs_remove(node->links[i]);
	kfree(node->links);
	node->links = NULL;
}