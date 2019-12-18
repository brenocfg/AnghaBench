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
typedef  int /*<<< orphan*/  u32 ;
struct p9_req_t {int fid; int /*<<< orphan*/  qid; int /*<<< orphan*/  rc; } ;
struct p9_qid {int /*<<< orphan*/  version; scalar_t__ path; int /*<<< orphan*/  type; } ;
struct p9_fid {int fid; int /*<<< orphan*/  qid; int /*<<< orphan*/  rc; } ;
struct p9_client {int /*<<< orphan*/  dotu; } ;

/* Variables and functions */
 struct p9_req_t* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int,...) ; 
 int P9_NOFID ; 
 int /*<<< orphan*/  P9_TATTACH ; 
 int PTR_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,struct p9_qid*,int) ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,int,int,char*,char*,int /*<<< orphan*/ ) ; 
 struct p9_req_t* p9_fid_create (struct p9_client*) ; 
 int /*<<< orphan*/  p9_fid_destroy (struct p9_req_t*) ; 
 int /*<<< orphan*/  p9_free_req (struct p9_client*,struct p9_req_t*) ; 
 int /*<<< orphan*/  p9pdu_dump (int,int /*<<< orphan*/ ) ; 
 int p9pdu_readf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct p9_qid*) ; 

struct p9_fid *p9_client_attach(struct p9_client *clnt, struct p9_fid *afid,
	char *uname, u32 n_uname, char *aname)
{
	int err;
	struct p9_req_t *req;
	struct p9_fid *fid;
	struct p9_qid qid;

	P9_DPRINTK(P9_DEBUG_9P, ">>> TATTACH afid %d uname %s aname %s\n",
					afid ? afid->fid : -1, uname, aname);
	err = 0;

	fid = p9_fid_create(clnt);
	if (IS_ERR(fid)) {
		err = PTR_ERR(fid);
		fid = NULL;
		goto error;
	}

	req = p9_client_rpc(clnt, P9_TATTACH, "ddss?d", fid->fid,
			afid ? afid->fid : P9_NOFID, uname, aname, n_uname);
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto error;
	}

	err = p9pdu_readf(req->rc, clnt->dotu, "Q", &qid);
	if (err) {
		p9pdu_dump(1, req->rc);
		p9_free_req(clnt, req);
		goto error;
	}

	P9_DPRINTK(P9_DEBUG_9P, "<<< RATTACH qid %x.%llx.%x\n",
					qid.type,
					(unsigned long long)qid.path,
					qid.version);

	memmove(&fid->qid, &qid, sizeof(struct p9_qid));

	p9_free_req(clnt, req);
	return fid;

error:
	if (fid)
		p9_fid_destroy(fid);
	return ERR_PTR(err);
}