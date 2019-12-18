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
struct ubifs_inode {int /*<<< orphan*/  data; } ;
struct nameidata {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  nd_set_link (struct nameidata*,int /*<<< orphan*/ ) ; 
 struct ubifs_inode* ubifs_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *ubifs_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	struct ubifs_inode *ui = ubifs_inode(dentry->d_inode);

	nd_set_link(nd, ui->data);
	return NULL;
}