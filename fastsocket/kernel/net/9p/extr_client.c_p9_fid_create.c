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
struct p9_qid {int dummy; } ;
struct p9_fid {int fid; int mode; int /*<<< orphan*/  flist; int /*<<< orphan*/ * rdir; struct p9_client* clnt; int /*<<< orphan*/  uid; int /*<<< orphan*/  qid; } ;
struct p9_client {int /*<<< orphan*/  lock; int /*<<< orphan*/  fidlist; int /*<<< orphan*/  fidpool; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 struct p9_fid* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  P9_DEBUG_FID ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct p9_client*) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  kfree (struct p9_fid*) ; 
 struct p9_fid* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int p9_idpool_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct p9_fid *p9_fid_create(struct p9_client *clnt)
{
	int ret;
	struct p9_fid *fid;
	unsigned long flags;

	P9_DPRINTK(P9_DEBUG_FID, "clnt %p\n", clnt);
	fid = kmalloc(sizeof(struct p9_fid), GFP_KERNEL);
	if (!fid)
		return ERR_PTR(-ENOMEM);

	ret = p9_idpool_get(clnt->fidpool);
	if (ret < 0) {
		ret = -ENOSPC;
		goto error;
	}
	fid->fid = ret;

	memset(&fid->qid, 0, sizeof(struct p9_qid));
	fid->mode = -1;
	fid->uid = current_fsuid();
	fid->clnt = clnt;
	fid->rdir = NULL;
	spin_lock_irqsave(&clnt->lock, flags);
	list_add(&fid->flist, &clnt->fidlist);
	spin_unlock_irqrestore(&clnt->lock, flags);

	return fid;

error:
	kfree(fid);
	return ERR_PTR(ret);
}