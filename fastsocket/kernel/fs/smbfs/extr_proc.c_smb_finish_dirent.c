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
struct smb_sb_info {TYPE_1__* mnt; } ;
struct smb_fattr {int f_mode; int attr; int f_size; int f_blocks; scalar_t__ f_unix; } ;
struct TYPE_2__ {int file_mode; int dir_mode; } ;

/* Variables and functions */
 int SMB_ST_BLKSIZE ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int aDIR ; 
 int aRONLY ; 

__attribute__((used)) static void
smb_finish_dirent(struct smb_sb_info *server, struct smb_fattr *fattr)
{
	if (fattr->f_unix)
		return;

	fattr->f_mode = server->mnt->file_mode;
	if (fattr->attr & aDIR) {
		fattr->f_mode = server->mnt->dir_mode;
		fattr->f_size = SMB_ST_BLKSIZE;
	}
	/* Check the read-only flag */
	if (fattr->attr & aRONLY)
		fattr->f_mode &= ~(S_IWUSR | S_IWGRP | S_IWOTH);

	/* How many 512 byte blocks do we need for this file? */
	fattr->f_blocks = 0;
	if (fattr->f_size != 0)
		fattr->f_blocks = 1 + ((fattr->f_size-1) >> 9);
	return;
}