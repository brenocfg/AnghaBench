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
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARANOIA (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 scalar_t__ smb_close (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static void
smb_delete_inode(struct inode *ino)
{
	DEBUG1("ino=%ld\n", ino->i_ino);
	truncate_inode_pages(&ino->i_data, 0);
	lock_kernel();
	if (smb_close(ino))
		PARANOIA("could not close inode %ld\n", ino->i_ino);
	unlock_kernel();
	clear_inode(ino);
}