#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; scalar_t__ len; } ;
struct dentry {struct dentry* d_parent; TYPE_1__ d_name; int /*<<< orphan*/  d_inode; } ;
struct TYPE_4__ {char* host_filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* HOSTFS_I (int /*<<< orphan*/ ) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,scalar_t__) ; 

__attribute__((used)) static char *dentry_name(struct dentry *dentry, int extra)
{
	struct dentry *parent;
	char *root, *name;
	int len;

	len = 0;
	parent = dentry;
	while (parent->d_parent != parent) {
		len += parent->d_name.len + 1;
		parent = parent->d_parent;
	}

	root = HOSTFS_I(parent->d_inode)->host_filename;
	len += strlen(root);
	name = kmalloc(len + extra + 1, GFP_KERNEL);
	if (name == NULL)
		return NULL;

	name[len] = '\0';
	parent = dentry;
	while (parent->d_parent != parent) {
		len -= parent->d_name.len + 1;
		name[len] = '/';
		strncpy(&name[len + 1], parent->d_name.name,
			parent->d_name.len);
		parent = parent->d_parent;
	}
	strncpy(name, root, strlen(root));
	return name;
}