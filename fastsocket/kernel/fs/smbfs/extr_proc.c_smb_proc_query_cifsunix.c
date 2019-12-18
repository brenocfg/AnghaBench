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
typedef  int /*<<< orphan*/  u64 ;
struct smb_sb_info {int dummy; } ;
struct smb_request {int rq_ldata; int rq_lparm; char* rq_parm; int /*<<< orphan*/ * rq_data; scalar_t__ rq_flags; int /*<<< orphan*/  rq_trans2_command; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 (char*,int,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LVAL (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PARANOIA (char*) ; 
 int /*<<< orphan*/  SMB_QUERY_CIFS_UNIX_INFO ; 
 int /*<<< orphan*/  TRANSACT2_QFSINFO ; 
 int /*<<< orphan*/  WSET (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WVAL (int /*<<< orphan*/ *,int) ; 
 int smb_add_request (struct smb_request*) ; 
 struct smb_request* smb_alloc_request (struct smb_sb_info*,int) ; 
 int /*<<< orphan*/  smb_rput (struct smb_request*) ; 

__attribute__((used)) static int
smb_proc_query_cifsunix(struct smb_sb_info *server)
{
	int result;
	int major, minor;
	u64 caps;
	char param[2];
	struct smb_request *req;

	result = -ENOMEM;
	if (! (req = smb_alloc_request(server, 100)))
		goto out;

	WSET(param, 0, SMB_QUERY_CIFS_UNIX_INFO);

	req->rq_trans2_command = TRANSACT2_QFSINFO;
	req->rq_ldata = 0;
	req->rq_data  = NULL;
	req->rq_lparm = 2;
	req->rq_parm  = param;
	req->rq_flags = 0;
	result = smb_add_request(req);
	if (result < 0)
		goto out_free;

	if (req->rq_ldata < 12) {
		PARANOIA("Not enough data\n");
		goto out_free;
	}
	major = WVAL(req->rq_data, 0);
	minor = WVAL(req->rq_data, 2);

	DEBUG1("Server implements CIFS Extensions for UNIX systems v%d.%d\n",
	       major, minor);
	/* FIXME: verify that we are ok with this major/minor? */

	caps = LVAL(req->rq_data, 4);
	DEBUG1("Server capabilities 0x%016llx\n", caps);

out_free:
	smb_rput(req);
out:
	return result;
}