#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct inode {scalar_t__ i_rdev; scalar_t__ i_private; TYPE_1__* i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {scalar_t__ s_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DEVPTS_SUPER_MAGIC ; 
 scalar_t__ MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTMX_MINOR ; 
 int /*<<< orphan*/  TTYAUX_MAJOR ; 
 struct dentry* d_find_alias (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

struct tty_struct *devpts_get_tty(struct inode *pts_inode, int number)
{
	struct dentry *dentry;
	struct tty_struct *tty;

	BUG_ON(pts_inode->i_rdev == MKDEV(TTYAUX_MAJOR, PTMX_MINOR));

	/* Ensure dentry has not been deleted by devpts_pty_kill() */
	dentry = d_find_alias(pts_inode);
	if (!dentry)
		return NULL;

	tty = NULL;
	if (pts_inode->i_sb->s_magic == DEVPTS_SUPER_MAGIC)
		tty = (struct tty_struct *)pts_inode->i_private;

	dput(dentry);

	return tty;
}