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
struct cifsInodeInfo {int clientCanCacheAll; int clientCanCacheRead; int /*<<< orphan*/  vfs_inode; } ;
typedef  int __u32 ;

/* Variables and functions */
 int OPLOCK_EXCLUSIVE ; 
 int OPLOCK_READ ; 
 int /*<<< orphan*/  cFYI (int,char*,int /*<<< orphan*/ *) ; 

void cifs_set_oplock_level(struct cifsInodeInfo *cinode, __u32 oplock)
{
	oplock &= 0xF;

	if (oplock == OPLOCK_EXCLUSIVE) {
		cinode->clientCanCacheAll = true;
		cinode->clientCanCacheRead = true;
		cFYI(1, "Exclusive Oplock granted on inode %p",
		     &cinode->vfs_inode);
	} else if (oplock == OPLOCK_READ) {
		cinode->clientCanCacheAll = false;
		cinode->clientCanCacheRead = true;
		cFYI(1, "Level II Oplock granted on inode %p",
		    &cinode->vfs_inode);
	} else {
		cinode->clientCanCacheAll = false;
		cinode->clientCanCacheRead = false;
	}
}