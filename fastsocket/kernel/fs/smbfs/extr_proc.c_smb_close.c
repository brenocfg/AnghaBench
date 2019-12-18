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
struct smb_sb_info {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct smb_sb_info* server_from_inode (struct inode*) ; 
 scalar_t__ smb_is_open (struct inode*) ; 
 int smb_proc_close_inode (struct smb_sb_info*,struct inode*) ; 

int
smb_close(struct inode *ino)
{
	int result = 0;

	if (smb_is_open(ino)) {
		struct smb_sb_info *server = server_from_inode(ino);
		result = smb_proc_close_inode(server, ino);
	}
	return result;
}