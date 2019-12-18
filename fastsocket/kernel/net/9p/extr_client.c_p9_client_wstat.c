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
struct TYPE_2__ {int /*<<< orphan*/  version; scalar_t__ path; int /*<<< orphan*/  type; } ;
struct p9_wstat {int /*<<< orphan*/  size; int /*<<< orphan*/  n_muid; int /*<<< orphan*/  n_gid; int /*<<< orphan*/  n_uid; int /*<<< orphan*/  extension; int /*<<< orphan*/  muid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  name; scalar_t__ length; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; int /*<<< orphan*/  mode; TYPE_1__ qid; int /*<<< orphan*/  dev; int /*<<< orphan*/  type; } ;
struct p9_req_t {int dummy; } ;
struct p9_fid {int /*<<< orphan*/  fid; struct p9_client* clnt; } ;
struct p9_client {int /*<<< orphan*/  dotu; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  P9_TWSTAT ; 
 int PTR_ERR (struct p9_req_t*) ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct p9_wstat*) ; 
 int /*<<< orphan*/  p9_client_statsize (struct p9_wstat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_free_req (struct p9_client*,struct p9_req_t*) ; 

int p9_client_wstat(struct p9_fid *fid, struct p9_wstat *wst)
{
	int err;
	struct p9_req_t *req;
	struct p9_client *clnt;

	err = 0;
	clnt = fid->clnt;
	wst->size = p9_client_statsize(wst, clnt->dotu);
	P9_DPRINTK(P9_DEBUG_9P, ">>> TWSTAT fid %d\n", fid->fid);
	P9_DPRINTK(P9_DEBUG_9P,
		"     sz=%x type=%x dev=%x qid=%x.%llx.%x\n"
		"     mode=%8.8x atime=%8.8x mtime=%8.8x length=%llx\n"
		"     name=%s uid=%s gid=%s muid=%s extension=(%s)\n"
		"     uid=%d gid=%d n_muid=%d\n",
		wst->size, wst->type, wst->dev, wst->qid.type,
		(unsigned long long)wst->qid.path, wst->qid.version, wst->mode,
		wst->atime, wst->mtime, (unsigned long long)wst->length,
		wst->name, wst->uid, wst->gid, wst->muid, wst->extension,
		wst->n_uid, wst->n_gid, wst->n_muid);

	req = p9_client_rpc(clnt, P9_TWSTAT, "dwS", fid->fid, wst->size, wst);
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto error;
	}

	P9_DPRINTK(P9_DEBUG_9P, "<<< RWSTAT fid %d\n", fid->fid);

	p9_free_req(clnt, req);
error:
	return err;
}