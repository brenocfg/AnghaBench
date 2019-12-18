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
struct smb_sb_info {int dummy; } ;
struct file {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  fileid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 TYPE_1__* SMB_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ) ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 int smb_proc_flush (struct smb_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smb_fsync(struct file *file, struct dentry * dentry, int datasync)
{
	struct smb_sb_info *server = server_from_dentry(dentry);
	int result;

	VERBOSE("sync file %s/%s\n", DENTRY_PATH(dentry));

	/*
	 * The VFS will writepage() all dirty pages for us, but we
	 * should send a SMBflush to the server, letting it know that
	 * we want things synchronized with actual storage.
	 *
	 * Note: this function requires all pages to have been written already
	 *       (should be ok with writepage_sync)
	 */
	result = smb_proc_flush(server, SMB_I(dentry->d_inode)->fileid);
	return result;
}