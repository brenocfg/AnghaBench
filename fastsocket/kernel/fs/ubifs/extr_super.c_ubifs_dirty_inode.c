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
struct ubifs_inode {int dirty; int /*<<< orphan*/  ui_mutex; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 

__attribute__((used)) static void ubifs_dirty_inode(struct inode *inode)
{
	struct ubifs_inode *ui = ubifs_inode(inode);

	ubifs_assert(mutex_is_locked(&ui->ui_mutex));
	if (!ui->dirty) {
		ui->dirty = 1;
		dbg_gen("inode %lu",  inode->i_ino);
	}
}