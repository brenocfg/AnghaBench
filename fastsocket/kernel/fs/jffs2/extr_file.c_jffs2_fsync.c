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
struct jffs2_sb_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 struct jffs2_sb_info* JFFS2_SB_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_flush_wbuf_gc (struct jffs2_sb_info*,int /*<<< orphan*/ ) ; 

int jffs2_fsync(struct file *filp, struct dentry *dentry, int datasync)
{
	struct inode *inode = dentry->d_inode;
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);

	/* Trigger GC to flush any pending writes for this inode */
	jffs2_flush_wbuf_gc(c, inode->i_ino);

	return 0;
}