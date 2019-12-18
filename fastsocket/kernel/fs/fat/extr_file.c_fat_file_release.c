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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int f_mode; } ;
struct TYPE_3__ {scalar_t__ flush; } ;
struct TYPE_4__ {TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int FMODE_WRITE ; 
 int HZ ; 
 TYPE_2__* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  congestion_wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fat_flush_inodes (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fat_file_release(struct inode *inode, struct file *filp)
{
	if ((filp->f_mode & FMODE_WRITE) &&
	     MSDOS_SB(inode->i_sb)->options.flush) {
		fat_flush_inodes(inode->i_sb, inode, NULL);
		congestion_wait(BLK_RW_ASYNC, HZ/10);
	}
	return 0;
}