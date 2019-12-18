#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int capabilities; scalar_t__ protocol; } ;
struct smb_sb_info {TYPE_3__ opt; } ;
struct smb_inode_info {scalar_t__ access; int /*<<< orphan*/  closed; scalar_t__ oldmtime; int /*<<< orphan*/  fileid; scalar_t__ open; } ;
struct smb_fattr {int dummy; } ;
struct TYPE_5__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_4__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct inode {TYPE_2__ i_mtime; TYPE_1__ i_atime; } ;

/* Variables and functions */
 int SMB_CAP_UNIX ; 
 struct smb_inode_info* SMB_I (struct inode*) ; 
 scalar_t__ SMB_O_RDONLY ; 
 scalar_t__ SMB_PROTOCOL_LANMAN2 ; 
 scalar_t__ SMB_PROTOCOL_NT1 ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  smb_get_inode_attr (struct inode*,struct smb_fattr*) ; 
 scalar_t__ smb_is_open (struct inode*) ; 
 int smb_proc_close (struct smb_sb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smb_proc_setattr_ext (struct smb_sb_info*,struct inode*,struct smb_fattr*) ; 

__attribute__((used)) static int 
smb_proc_close_inode(struct smb_sb_info *server, struct inode * ino)
{
	struct smb_inode_info *ei = SMB_I(ino);
	int result = 0;
	if (smb_is_open(ino))
	{
		/*
		 * We clear the open flag in advance, in case another
 		 * process observes the value while we block below.
		 */
		ei->open = 0;

		/*
		 * Kludge alert: SMB timestamps are accurate only to
		 * two seconds ... round the times to avoid needless
		 * cache invalidations!
		 */
		if (ino->i_mtime.tv_sec & 1) { 
			ino->i_mtime.tv_sec--;
			ino->i_mtime.tv_nsec = 0; 
		}
		if (ino->i_atime.tv_sec & 1) {
			ino->i_atime.tv_sec--;
			ino->i_atime.tv_nsec = 0;
		}
		/*
		 * If the file is open with write permissions,
		 * update the time stamps to sync mtime and atime.
		 */
		if ((server->opt.capabilities & SMB_CAP_UNIX) == 0 &&
		    (server->opt.protocol >= SMB_PROTOCOL_LANMAN2) &&
		    !(ei->access == SMB_O_RDONLY))
		{
			struct smb_fattr fattr;
			smb_get_inode_attr(ino, &fattr);
			smb_proc_setattr_ext(server, ino, &fattr);
		}

		result = smb_proc_close(server, ei->fileid, ino->i_mtime.tv_sec);
		/*
		 * Force a revalidation after closing ... some servers
		 * don't post the size until the file has been closed.
		 */
		if (server->opt.protocol < SMB_PROTOCOL_NT1)
			ei->oldmtime = 0;
		ei->closed = jiffies;
	}
	return result;
}