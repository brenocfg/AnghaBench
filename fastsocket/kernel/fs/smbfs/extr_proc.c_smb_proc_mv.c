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
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SMBmv ; 
 int /*<<< orphan*/  WSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int aDIR ; 
 int aHIDDEN ; 
 int aSYSTEM ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 struct smb_request* smb_alloc_request (struct smb_sb_info*,int /*<<< orphan*/ ) ; 
 int smb_request_ok (struct smb_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_rput (struct smb_request*) ; 
 int /*<<< orphan*/  smb_setup_bcc (struct smb_request*,char*) ; 
 char* smb_setup_header (struct smb_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int smb_simple_encode_path (struct smb_request*,char**,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_vwv0 ; 

int
smb_proc_mv(struct dentry *old_dentry, struct dentry *new_dentry)
{
	struct smb_sb_info *server = server_from_dentry(old_dentry);
	char *p;
	int result;
	struct smb_request *req;

	result = -ENOMEM;
	if (! (req = smb_alloc_request(server, PAGE_SIZE)))
		goto out;

	p = smb_setup_header(req, SMBmv, 1, 0);
	WSET(req->rq_header, smb_vwv0, aSYSTEM | aHIDDEN | aDIR);
	result = smb_simple_encode_path(req, &p, old_dentry, NULL);
	if (result < 0)
		goto out_free;
	result = smb_simple_encode_path(req, &p, new_dentry, NULL);
	if (result < 0)
		goto out_free;
	smb_setup_bcc(req, p);

	if ((result = smb_request_ok(req, SMBmv, 0, 0)) < 0)
		goto out_free;
	result = 0;

out_free:
	smb_rput(req);
out:
	return result;
}