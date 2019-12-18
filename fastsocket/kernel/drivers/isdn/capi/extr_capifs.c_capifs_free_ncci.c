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
struct inode {int /*<<< orphan*/  i_nlink; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_4__ {TYPE_1__* d_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 TYPE_2__* capifs_root ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* get_node (unsigned int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void capifs_free_ncci(unsigned int number)
{
	struct dentry *dentry = get_node(number);

	if (!IS_ERR(dentry)) {
		struct inode *inode = dentry->d_inode;
		if (inode) {
			inode->i_nlink--;
			d_delete(dentry);
			dput(dentry);
		}
		dput(dentry);
	}
	mutex_unlock(&capifs_root->d_inode->i_mutex);
}