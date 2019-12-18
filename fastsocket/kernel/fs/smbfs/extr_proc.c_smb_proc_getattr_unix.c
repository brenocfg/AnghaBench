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
struct smb_request {int /*<<< orphan*/  rq_data; } ;
struct smb_fattr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SMB_QUERY_FILE_UNIX_BASIC ; 
 struct smb_request* smb_alloc_request (struct smb_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_decode_unix_basic (struct smb_fattr*,struct smb_sb_info*,int /*<<< orphan*/ ) ; 
 int smb_proc_getattr_trans2 (struct smb_sb_info*,struct dentry*,struct smb_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_rput (struct smb_request*) ; 

__attribute__((used)) static int
smb_proc_getattr_unix(struct smb_sb_info *server, struct dentry *dir,
		      struct smb_fattr *attr)
{
	struct smb_request *req;
	int result;

	result = -ENOMEM;
	if (! (req = smb_alloc_request(server, PAGE_SIZE)))
		goto out;

	result = smb_proc_getattr_trans2(server, dir, req,
					 SMB_QUERY_FILE_UNIX_BASIC);
	if (result < 0)
		goto out_free;

	smb_decode_unix_basic(attr, server, req->rq_data);

out_free:
	smb_rput(req);
out:
	return result;
}