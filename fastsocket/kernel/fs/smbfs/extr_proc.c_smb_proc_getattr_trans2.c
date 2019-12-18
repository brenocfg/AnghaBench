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
struct smb_request {char* rq_buffer; int rq_ldata; int rq_lparm; char* rq_parm; int /*<<< orphan*/  rq_err; int /*<<< orphan*/  rq_rcls; scalar_t__ rq_flags; int /*<<< orphan*/ * rq_data; int /*<<< orphan*/  rq_trans2_command; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSET (char*,int,int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  PARANOIA (char*,char*,int) ; 
 scalar_t__ SMB_MAXPATHLEN ; 
 int /*<<< orphan*/  TRANSACT2_QPATHINFO ; 
 int /*<<< orphan*/  VERBOSE (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSET (char*,int /*<<< orphan*/ ,int) ; 
 int smb_add_request (struct smb_request*) ; 
 int smb_encode_path (struct smb_sb_info*,char*,scalar_t__,struct dentry*,int /*<<< orphan*/ *) ; 
 int smb_errno (struct smb_request*) ; 

__attribute__((used)) static int
smb_proc_getattr_trans2(struct smb_sb_info *server, struct dentry *dir,
			struct smb_request *req, int infolevel)
{
	char *p, *param;
	int result;

	param = req->rq_buffer;
	WSET(param, 0, infolevel);
	DSET(param, 2, 0);
	result = smb_encode_path(server, param+6, SMB_MAXPATHLEN+1, dir, NULL);
	if (result < 0)
		goto out;
	p = param + 6 + result;

	req->rq_trans2_command = TRANSACT2_QPATHINFO;
	req->rq_ldata = 0;
	req->rq_data  = NULL;
	req->rq_lparm = p - param;
	req->rq_parm  = param;
	req->rq_flags = 0;
	result = smb_add_request(req);
	if (result < 0)
		goto out;
	if (req->rq_rcls != 0) {
		VERBOSE("for %s: result=%d, rcls=%d, err=%d\n",
			&param[6], result, req->rq_rcls, req->rq_err);
		result = smb_errno(req);
		goto out;
	}
	result = -ENOENT;
	if (req->rq_ldata < 22) {
		PARANOIA("not enough data for %s, len=%d\n",
			 &param[6], req->rq_ldata);
		goto out;
	}

	result = 0;
out:
	return result;
}