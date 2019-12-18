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
struct p9_req_t {int fid; int /*<<< orphan*/  qid; int /*<<< orphan*/  rc; int /*<<< orphan*/  uid; struct p9_client* clnt; } ;
struct p9_qid {int type; char* version; scalar_t__ path; } ;
struct p9_fid {int fid; int /*<<< orphan*/  qid; int /*<<< orphan*/  rc; int /*<<< orphan*/  uid; struct p9_client* clnt; } ;
struct p9_client {int /*<<< orphan*/  dotu; } ;
typedef  int int16_t ;

/* Variables and functions */
 int ENOENT ; 
 struct p9_req_t* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  P9_TWALK ; 
 int PTR_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,struct p9_qid*,int) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_req_t*) ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,int,int,int,char**) ; 
 struct p9_req_t* p9_fid_create (struct p9_client*) ; 
 int /*<<< orphan*/  p9_fid_destroy (struct p9_req_t*) ; 
 int /*<<< orphan*/  p9_free_req (struct p9_client*,struct p9_req_t*) ; 
 int /*<<< orphan*/  p9pdu_dump (int,int /*<<< orphan*/ ) ; 
 int p9pdu_readf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,struct p9_qid**) ; 

struct p9_fid *p9_client_walk(struct p9_fid *oldfid, int nwname, char **wnames,
	int clone)
{
	int err;
	struct p9_client *clnt;
	struct p9_fid *fid;
	struct p9_qid *wqids;
	struct p9_req_t *req;
	int16_t nwqids, count;

	err = 0;
	clnt = oldfid->clnt;
	if (clone) {
		fid = p9_fid_create(clnt);
		if (IS_ERR(fid)) {
			err = PTR_ERR(fid);
			fid = NULL;
			goto error;
		}

		fid->uid = oldfid->uid;
	} else
		fid = oldfid;


	P9_DPRINTK(P9_DEBUG_9P, ">>> TWALK fids %d,%d nwname %d wname[0] %s\n",
		oldfid->fid, fid->fid, nwname, wnames ? wnames[0] : NULL);

	req = p9_client_rpc(clnt, P9_TWALK, "ddT", oldfid->fid, fid->fid,
								nwname, wnames);
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto error;
	}

	err = p9pdu_readf(req->rc, clnt->dotu, "R", &nwqids, &wqids);
	if (err) {
		p9pdu_dump(1, req->rc);
		p9_free_req(clnt, req);
		goto clunk_fid;
	}
	p9_free_req(clnt, req);

	P9_DPRINTK(P9_DEBUG_9P, "<<< RWALK nwqid %d:\n", nwqids);

	if (nwqids != nwname) {
		err = -ENOENT;
		goto clunk_fid;
	}

	for (count = 0; count < nwqids; count++)
		P9_DPRINTK(P9_DEBUG_9P, "<<<     [%d] %x.%llx.%x\n",
			count, wqids[count].type,
			(unsigned long long)wqids[count].path,
			wqids[count].version);

	if (nwname)
		memmove(&fid->qid, &wqids[nwqids - 1], sizeof(struct p9_qid));
	else
		fid->qid = oldfid->qid;

	return fid;

clunk_fid:
	p9_client_clunk(fid);
	fid = NULL;

error:
	if (fid && (fid != oldfid))
		p9_fid_destroy(fid);

	return ERR_PTR(err);
}