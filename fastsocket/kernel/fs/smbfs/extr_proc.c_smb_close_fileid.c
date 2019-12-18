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
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  get_seconds () ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 int smb_proc_close (struct smb_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
smb_close_fileid(struct dentry *dentry, __u16 fileid)
{
	struct smb_sb_info *server = server_from_dentry(dentry);
	int result;

	result = smb_proc_close(server, fileid, get_seconds());
	return result;
}