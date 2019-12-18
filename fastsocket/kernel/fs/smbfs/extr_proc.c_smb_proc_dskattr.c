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
struct smb_request {int /*<<< orphan*/  rq_header; } ;
struct kstatfs {long f_blocks; long f_bavail; long f_bfree; int /*<<< orphan*/  f_bsize; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct smb_sb_info* SMB_SB (int /*<<< orphan*/ ) ; 
 long SMB_ST_BLKSHIFT ; 
 int /*<<< orphan*/  SMB_ST_BLKSIZE ; 
 char* SMB_VWV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMBdskattr ; 
 long WVAL (char*,int) ; 
 struct smb_request* smb_alloc_request (struct smb_sb_info*,int /*<<< orphan*/ ) ; 
 int smb_request_ok (struct smb_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_rput (struct smb_request*) ; 
 int /*<<< orphan*/  smb_setup_header (struct smb_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
smb_proc_dskattr(struct dentry *dentry, struct kstatfs *attr)
{
	struct smb_sb_info *server = SMB_SB(dentry->d_sb);
	int result;
	char *p;
	long unit;
	struct smb_request *req;

	result = -ENOMEM;
	if (! (req = smb_alloc_request(server, 0)))
		goto out;

	smb_setup_header(req, SMBdskattr, 0, 0);
	if ((result = smb_request_ok(req, SMBdskattr, 5, 0)) < 0)
		goto out_free;
	p = SMB_VWV(req->rq_header);
	unit = (WVAL(p, 2) * WVAL(p, 4)) >> SMB_ST_BLKSHIFT;
	attr->f_blocks = WVAL(p, 0) * unit;
	attr->f_bsize  = SMB_ST_BLKSIZE;
	attr->f_bavail = attr->f_bfree = WVAL(p, 6) * unit;
	result = 0;

out_free:
	smb_rput(req);
out:
	return result;
}