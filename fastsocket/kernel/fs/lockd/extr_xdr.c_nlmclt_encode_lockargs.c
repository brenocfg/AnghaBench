#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_rqst {int /*<<< orphan*/  rq_svec; int /*<<< orphan*/  rq_slen; } ;
struct TYPE_4__ {scalar_t__ fl_type; } ;
struct nlm_lock {TYPE_1__ fl; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; scalar_t__ reclaim; scalar_t__ block; int /*<<< orphan*/  cookie; struct nlm_lock lock; } ;
typedef  TYPE_2__ nlm_args ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ F_WRLCK ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nlm_encode_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nlm_encode_lock (int /*<<< orphan*/ *,struct nlm_lock*) ; 
 int /*<<< orphan*/  xdr_adjust_iovec (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* xdr_one ; 
 void* xdr_zero ; 

__attribute__((used)) static int
nlmclt_encode_lockargs(struct rpc_rqst *req, __be32 *p, nlm_args *argp)
{
	struct nlm_lock	*lock = &argp->lock;

	if (!(p = nlm_encode_cookie(p, &argp->cookie)))
		return -EIO;
	*p++ = argp->block? xdr_one : xdr_zero;
	*p++ = (lock->fl.fl_type == F_WRLCK)? xdr_one : xdr_zero;
	if (!(p = nlm_encode_lock(p, lock)))
		return -EIO;
	*p++ = argp->reclaim? xdr_one : xdr_zero;
	*p++ = htonl(argp->state);
	req->rq_slen = xdr_adjust_iovec(req->rq_svec, p);
	return 0;
}