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
struct smb_request {char* rq_buffer; int rq_ldata; char* rq_data; int rq_lparm; char* rq_parm; scalar_t__ rq_rcls; int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  rq_trans2_command; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  fileid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LSET (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* SMB_I (struct inode*) ; 
 int /*<<< orphan*/  SMB_REQ_NORETRY ; 
 int /*<<< orphan*/  SMB_SET_FILE_END_OF_FILE_INFO ; 
 int /*<<< orphan*/  TRANSACT2_SETFILEINFO ; 
 int /*<<< orphan*/  WSET (char*,int,int /*<<< orphan*/ ) ; 
 struct smb_sb_info* server_from_inode (struct inode*) ; 
 int smb_add_request (struct smb_request*) ; 
 struct smb_request* smb_alloc_request (struct smb_sb_info*,int) ; 
 int smb_errno (struct smb_request*) ; 
 int /*<<< orphan*/  smb_rput (struct smb_request*) ; 

__attribute__((used)) static int
smb_proc_trunc64(struct inode *inode, loff_t length)
{
	struct smb_sb_info *server = server_from_inode(inode);
	int result;
	char *param;
	char *data;
	struct smb_request *req;

	result = -ENOMEM;
	if (! (req = smb_alloc_request(server, 14)))
		goto out;

	param = req->rq_buffer;
	data = req->rq_buffer + 6;

	/* FIXME: must we also set allocation size? winNT seems to do that */
	WSET(param, 0, SMB_I(inode)->fileid);
	WSET(param, 2, SMB_SET_FILE_END_OF_FILE_INFO);
	WSET(param, 4, 0);
	LSET(data, 0, length);

	req->rq_trans2_command = TRANSACT2_SETFILEINFO;
	req->rq_ldata = 8;
	req->rq_data  = data;
	req->rq_lparm = 6;
	req->rq_parm  = param;
	req->rq_flags |= SMB_REQ_NORETRY;
	result = smb_add_request(req);
	if (result < 0)
		goto out_free;

	result = 0;
	if (req->rq_rcls != 0)
		result = smb_errno(req);

out_free:
	smb_rput(req);
out:
	return result;
}