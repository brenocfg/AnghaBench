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
struct smb_request {int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  rq_header; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  DSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SMB_REQ_NORETRY ; 
 int /*<<< orphan*/  SMBclose ; 
 int /*<<< orphan*/  WSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct smb_request* smb_alloc_request (struct smb_sb_info*,int /*<<< orphan*/ ) ; 
 int smb_request_ok (struct smb_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_rput (struct smb_request*) ; 
 int /*<<< orphan*/  smb_setup_header (struct smb_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_vwv0 ; 
 int /*<<< orphan*/  smb_vwv1 ; 
 int /*<<< orphan*/  utc2local (struct smb_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
smb_proc_close(struct smb_sb_info *server, __u16 fileid, __u32 mtime)
{
	struct smb_request *req;
	int result = -ENOMEM;

	if (! (req = smb_alloc_request(server, 0)))
		goto out;

	smb_setup_header(req, SMBclose, 3, 0);
	WSET(req->rq_header, smb_vwv0, fileid);
	DSET(req->rq_header, smb_vwv1, utc2local(server, mtime));
	req->rq_flags |= SMB_REQ_NORETRY;
	result = smb_request_ok(req, SMBclose, 0, 0);

	smb_rput(req);
out:
	return result;
}