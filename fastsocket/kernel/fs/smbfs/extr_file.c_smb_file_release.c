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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  openers; } ;

/* Variables and functions */
 TYPE_1__* SMB_I (struct inode*) ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  smb_close (struct inode*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
smb_file_release(struct inode *inode, struct file * file)
{
	lock_kernel();
	if (!--SMB_I(inode)->openers) {
		/* We must flush any dirty pages now as we won't be able to
		   write anything after close. mmap can trigger this.
		   "openers" should perhaps include mmap'ers ... */
		filemap_write_and_wait(inode->i_mapping);
		smb_close(inode);
	}
	unlock_kernel();
	return 0;
}