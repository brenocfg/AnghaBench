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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct cifs_sb_info {int mnt_cifs_flags; } ;

/* Variables and functions */
 int CIFS_MOUNT_SERVER_INUM ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 void generic_delete_inode (struct inode*) ; 
 void generic_drop_inode (struct inode*) ; 

void cifs_drop_inode(struct inode *inode)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM)
		return generic_drop_inode(inode);

	return generic_delete_inode(inode);
}