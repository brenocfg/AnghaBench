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
struct p9_fid {struct p9_fid* rdir; int /*<<< orphan*/  flist; int /*<<< orphan*/  fid; struct p9_client* clnt; } ;
struct p9_client {int /*<<< orphan*/  lock; int /*<<< orphan*/  fidpool; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FID ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct p9_fid*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_idpool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void p9_fid_destroy(struct p9_fid *fid)
{
	struct p9_client *clnt;
	unsigned long flags;

	P9_DPRINTK(P9_DEBUG_FID, "fid %d\n", fid->fid);
	clnt = fid->clnt;
	p9_idpool_put(fid->fid, clnt->fidpool);
	spin_lock_irqsave(&clnt->lock, flags);
	list_del(&fid->flist);
	spin_unlock_irqrestore(&clnt->lock, flags);
	kfree(fid->rdir);
	kfree(fid);
}