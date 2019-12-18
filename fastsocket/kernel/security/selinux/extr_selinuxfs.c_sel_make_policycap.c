#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {unsigned int i_ino; int /*<<< orphan*/ * i_fop; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 int ENOMEM ; 
 unsigned int POLICYDB_CAPABILITY_MAX ; 
 unsigned int SEL_POLICYCAP_INO_OFFSET ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (TYPE_1__*,char*) ; 
 TYPE_1__* policycap_dir ; 
 char** policycap_names ; 
 struct inode* sel_make_inode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sel_policycap_ops ; 
 int /*<<< orphan*/  sel_remove_entries (TYPE_1__*) ; 

__attribute__((used)) static int sel_make_policycap(void)
{
	unsigned int iter;
	struct dentry *dentry = NULL;
	struct inode *inode = NULL;

	sel_remove_entries(policycap_dir);

	for (iter = 0; iter <= POLICYDB_CAPABILITY_MAX; iter++) {
		if (iter < ARRAY_SIZE(policycap_names))
			dentry = d_alloc_name(policycap_dir,
					      policycap_names[iter]);
		else
			dentry = d_alloc_name(policycap_dir, "unknown");

		if (dentry == NULL)
			return -ENOMEM;

		inode = sel_make_inode(policycap_dir->d_sb, S_IFREG | S_IRUGO);
		if (inode == NULL)
			return -ENOMEM;

		inode->i_fop = &sel_policycap_ops;
		inode->i_ino = iter | SEL_POLICYCAP_INO_OFFSET;
		d_add(dentry, inode);
	}

	return 0;
}