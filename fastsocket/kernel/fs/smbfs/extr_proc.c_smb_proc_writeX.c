#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct smb_sb_info {int dummy; } ;
struct smb_request {int rq_iovlen; int /*<<< orphan*/  rq_header; int /*<<< orphan*/  rq_flags; TYPE_1__* rq_iov; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
typedef  int loff_t ;
struct TYPE_4__ {int fileid; } ;
struct TYPE_3__ {char* iov_base; int iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 TYPE_2__* SMB_I (struct inode*) ; 
 int /*<<< orphan*/  SMB_REQ_NORETRY ; 
 int /*<<< orphan*/  SMBwriteX ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  WSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int WVAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct smb_sb_info* server_from_inode (struct inode*) ; 
 struct smb_request* smb_alloc_request (struct smb_sb_info*,int /*<<< orphan*/ ) ; 
 int smb_request_ok (struct smb_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_rput (struct smb_request*) ; 
 char* smb_setup_header (struct smb_request*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  smb_vwv0 ; 
 int /*<<< orphan*/  smb_vwv1 ; 
 int /*<<< orphan*/  smb_vwv10 ; 
 int /*<<< orphan*/  smb_vwv11 ; 
 int smb_vwv12 ; 
 int /*<<< orphan*/  smb_vwv2 ; 
 int smb_vwv3 ; 
 int smb_vwv5 ; 
 int /*<<< orphan*/  smb_vwv7 ; 
 int /*<<< orphan*/  smb_vwv8 ; 
 int /*<<< orphan*/  smb_vwv9 ; 

__attribute__((used)) static int
smb_proc_writeX(struct inode *inode, loff_t offset, int count, const char *data)
{
	struct smb_sb_info *server = server_from_inode(inode);
	int result;
	u8 *p;
	static u8 pad[4];
	struct smb_request *req;

	result = -ENOMEM;
	if (! (req = smb_alloc_request(server, 0)))
		goto out;

	VERBOSE("ino=%ld, fileid=%d, count=%d@%Ld\n",
		inode->i_ino, SMB_I(inode)->fileid, count, offset);

	p = smb_setup_header(req, SMBwriteX, 14, count + 1);
	WSET(req->rq_header, smb_vwv0, 0x00ff);
	WSET(req->rq_header, smb_vwv1, 0);
	WSET(req->rq_header, smb_vwv2, SMB_I(inode)->fileid);
	DSET(req->rq_header, smb_vwv3, (u32)offset);	/* low 32 bits */
	DSET(req->rq_header, smb_vwv5, 0);
	WSET(req->rq_header, smb_vwv7, 0);		/* write mode */
	WSET(req->rq_header, smb_vwv8, 0);
	WSET(req->rq_header, smb_vwv9, 0);
	WSET(req->rq_header, smb_vwv10, count);		/* data length */
	WSET(req->rq_header, smb_vwv11, smb_vwv12 + 2 + 1);
	DSET(req->rq_header, smb_vwv12, (u32)(offset >> 32));

	req->rq_iov[1].iov_base = pad;
	req->rq_iov[1].iov_len = 1;
	req->rq_iov[2].iov_base = (char *) data;
	req->rq_iov[2].iov_len = count;
	req->rq_iovlen = 3;
	req->rq_flags |= SMB_REQ_NORETRY;

	result = smb_request_ok(req, SMBwriteX, 6, 0);
 	if (result >= 0)
		result = WVAL(req->rq_header, smb_vwv2);

	smb_rput(req);
out:
	return result;
}