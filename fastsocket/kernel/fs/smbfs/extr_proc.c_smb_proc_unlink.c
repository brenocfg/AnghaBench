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
struct smb_request {scalar_t__ rq_flags; int /*<<< orphan*/  rq_header; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SMBunlink ; 
 int /*<<< orphan*/  WSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int aHIDDEN ; 
 int aSYSTEM ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 struct smb_request* smb_alloc_request (struct smb_sb_info*,int /*<<< orphan*/ ) ; 
 int smb_request_ok (struct smb_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_rput (struct smb_request*) ; 
 int smb_set_rw (struct dentry*,struct smb_sb_info*) ; 
 int /*<<< orphan*/  smb_setup_bcc (struct smb_request*,char*) ; 
 char* smb_setup_header (struct smb_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int smb_simple_encode_path (struct smb_request*,char**,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_vwv0 ; 

int
smb_proc_unlink(struct dentry *dentry)
{
	struct smb_sb_info *server = server_from_dentry(dentry);
	int flag = 0;
	char *p;
	int result;
	struct smb_request *req;

	result = -ENOMEM;
	if (! (req = smb_alloc_request(server, PAGE_SIZE)))
		goto out;

      retry:
	p = smb_setup_header(req, SMBunlink, 1, 0);
	WSET(req->rq_header, smb_vwv0, aSYSTEM | aHIDDEN);
	result = smb_simple_encode_path(req, &p, dentry, NULL);
	if (result < 0)
		goto out_free;
	smb_setup_bcc(req, p);

	if ((result = smb_request_ok(req, SMBunlink, 0, 0)) < 0) {
#if SMBFS_POSIX_UNLINK
		if (result == -EACCES && !flag) {
			/* Posix semantics is for the read-only state
			   of a file to be ignored in unlink(). In the
			   SMB world a unlink() is refused on a
			   read-only file. To make things easier for
			   unix users we try to override the files
			   permission if the unlink fails with the
			   right error.
			   This introduces a race condition that could
			   lead to a file being written by someone who
			   shouldn't have access, but as far as I can
			   tell that is unavoidable */

			/* remove RONLY attribute and try again */
			result = smb_set_rw(dentry,server);
			if (result == 0) {
				flag = 1;
				req->rq_flags = 0;
				goto retry;
			}
		}
#endif
		goto out_free;
	}
	result = 0;

out_free:
	smb_rput(req);
out:
	return result;
}