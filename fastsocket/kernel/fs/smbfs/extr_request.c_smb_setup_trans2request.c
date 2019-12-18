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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int const max_xmit; } ;
struct smb_sb_info {TYPE_1__ opt; } ;
struct smb_request {int const rq_lparm; unsigned char* rq_data; int const rq_ldata; int rq_bufsize; int* rq_header; int const rq_trans2_command; int rq_iovlen; unsigned char* rq_parm; int rq_slen; int /*<<< orphan*/  rq_setup_read; TYPE_2__* rq_iov; struct smb_sb_info* rq_server; } ;
struct TYPE_4__ {unsigned char* iov_base; int iov_len; } ;

/* Variables and functions */
 int ALIGN (int const,int) ; 
 int /*<<< orphan*/  DSET (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int SMB_HEADER_LEN ; 
 int SMB_TRANS2_MAX_PARAM ; 
 int /*<<< orphan*/  SMBtrans2 ; 
 int /*<<< orphan*/  WSET (int*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  smb_dscnt ; 
 int /*<<< orphan*/  smb_dsoff ; 
 int /*<<< orphan*/  smb_flags ; 
 int /*<<< orphan*/  smb_mdrcnt ; 
 int /*<<< orphan*/  smb_mprcnt ; 
 int /*<<< orphan*/  smb_msrcnt ; 
 int /*<<< orphan*/  smb_pscnt ; 
 int /*<<< orphan*/  smb_psoff ; 
 int /*<<< orphan*/  smb_setup0 ; 
 int /*<<< orphan*/  smb_setup_bcc ; 
 int /*<<< orphan*/  smb_setup_header (struct smb_request*,int /*<<< orphan*/ ,int const,int const) ; 
 int smb_suwcnt ; 
 int /*<<< orphan*/  smb_tdscnt ; 
 int /*<<< orphan*/  smb_timeout ; 
 int /*<<< orphan*/  smb_tpscnt ; 

__attribute__((used)) static int smb_setup_trans2request(struct smb_request *req)
{
	struct smb_sb_info *server = req->rq_server;
	int mparam, mdata;
	static unsigned char padding[4];

	/* I know the following is very ugly, but I want to build the
	   smb packet as efficiently as possible. */

	const int smb_parameters = 15;
	const int header = SMB_HEADER_LEN + 2 * smb_parameters + 2;
	const int oparam = ALIGN(header + 3, sizeof(u32));
	const int odata  = ALIGN(oparam + req->rq_lparm, sizeof(u32));
	const int bcc = (req->rq_data ? odata + req->rq_ldata :
					oparam + req->rq_lparm) - header;

	if ((bcc + oparam) > server->opt.max_xmit)
		return -ENOMEM;
	smb_setup_header(req, SMBtrans2, smb_parameters, bcc);

	/*
	 * max parameters + max data + max setup == bufsize to make NT4 happy
	 * and not abort the transfer or split into multiple responses. It also
	 * makes smbfs happy as handling packets larger than the buffer size
	 * is extra work.
	 *
	 * OS/2 is probably going to hate me for this ...
	 */
	mparam = SMB_TRANS2_MAX_PARAM;
	mdata = req->rq_bufsize - mparam;

	mdata = server->opt.max_xmit - mparam - 100;
	if (mdata < 1024) {
		mdata = 1024;
		mparam = 20;
	}

#if 0
	/* NT/win2k has ~4k max_xmit, so with this we request more than it wants
	   to return as one SMB. Useful for testing the fragmented trans2
	   handling. */
	mdata = 8192;
#endif

	WSET(req->rq_header, smb_tpscnt, req->rq_lparm);
	WSET(req->rq_header, smb_tdscnt, req->rq_ldata);
	WSET(req->rq_header, smb_mprcnt, mparam);
	WSET(req->rq_header, smb_mdrcnt, mdata);
	WSET(req->rq_header, smb_msrcnt, 0);    /* max setup always 0 ? */
	WSET(req->rq_header, smb_flags, 0);
	DSET(req->rq_header, smb_timeout, 0);
	WSET(req->rq_header, smb_pscnt, req->rq_lparm);
	WSET(req->rq_header, smb_psoff, oparam - 4);
	WSET(req->rq_header, smb_dscnt, req->rq_ldata);
	WSET(req->rq_header, smb_dsoff, req->rq_data ? odata - 4 : 0);
	*(req->rq_header + smb_suwcnt) = 0x01;          /* setup count */
	*(req->rq_header + smb_suwcnt + 1) = 0x00;      /* reserved */
	WSET(req->rq_header, smb_setup0, req->rq_trans2_command);

	req->rq_iovlen = 2;
	req->rq_iov[0].iov_base = (void *) req->rq_header;
	req->rq_iov[0].iov_len = oparam;
	req->rq_iov[1].iov_base = (req->rq_parm==NULL) ? padding : req->rq_parm;
	req->rq_iov[1].iov_len = req->rq_lparm;
	req->rq_slen = oparam + req->rq_lparm;

	if (req->rq_data) {
		req->rq_iovlen += 2;
		req->rq_iov[2].iov_base = padding;
		req->rq_iov[2].iov_len = odata - oparam - req->rq_lparm;
		req->rq_iov[3].iov_base = req->rq_data;
		req->rq_iov[3].iov_len = req->rq_ldata;
		req->rq_slen = odata + req->rq_ldata;
	}

	/* always a data part for trans2 replies */
	req->rq_setup_read = smb_setup_bcc;

	return 0;
}