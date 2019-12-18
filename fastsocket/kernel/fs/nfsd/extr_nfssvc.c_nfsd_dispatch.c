#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* head; } ;
struct TYPE_6__ {TYPE_1__* head; } ;
struct svc_rqst {int rq_vers; scalar_t__ rq_proc; int /*<<< orphan*/  rq_cachetype; int /*<<< orphan*/  rq_resp; scalar_t__ rq_dropme; int /*<<< orphan*/  rq_argp; TYPE_4__ rq_res; TYPE_2__ rq_arg; struct svc_procedure* rq_procinfo; } ;
struct svc_procedure {scalar_t__ (* pc_func ) (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pc_encode ) (struct svc_rqst*,scalar_t__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pc_decode ) (struct svc_rqst*,scalar_t__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pc_cachetype; } ;
typedef  int /*<<< orphan*/  (* kxdrproc_t ) (struct svc_rqst*,scalar_t__*,int /*<<< orphan*/ ) ;
typedef  scalar_t__ __be32 ;
struct TYPE_7__ {int iov_len; scalar_t__* iov_base; } ;
struct TYPE_5__ {scalar_t__ iov_base; } ;

/* Variables and functions */
#define  RC_DOIT 130 
#define  RC_DROPIT 129 
 int /*<<< orphan*/  RC_NOCACHE ; 
#define  RC_REPLY 128 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 scalar_t__ map_new_errors (int,scalar_t__) ; 
 int nfsd_cache_lookup (struct svc_rqst*) ; 
 int /*<<< orphan*/  nfsd_cache_update (struct svc_rqst*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ nfserr_dropit ; 
 scalar_t__ rpc_garbage_args ; 
 scalar_t__ rpc_system_err ; 
 scalar_t__ stub1 (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nfsd_dispatch(struct svc_rqst *rqstp, __be32 *statp)
{
	struct svc_procedure	*proc;
	kxdrproc_t		xdr;
	__be32			nfserr;
	__be32			*nfserrp;

	dprintk("nfsd_dispatch: vers %d proc %d\n",
				rqstp->rq_vers, rqstp->rq_proc);
	proc = rqstp->rq_procinfo;

	/*
	 * Give the xdr decoder a chance to change this if it wants
	 * (necessary in the NFSv4.0 compound case)
	 */
	rqstp->rq_cachetype = proc->pc_cachetype;
	/* Decode arguments */
	xdr = proc->pc_decode;
	if (xdr && !xdr(rqstp, (__be32*)rqstp->rq_arg.head[0].iov_base,
			rqstp->rq_argp)) {
		dprintk("nfsd: failed to decode arguments!\n");
		*statp = rpc_garbage_args;
		return 1;
	}

	/* Check whether we have this call in the cache. */
	switch (nfsd_cache_lookup(rqstp)) {
	case RC_DROPIT:
		return 0;
	case RC_REPLY:
		return 1;
	case RC_DOIT:;
		/* do it */
	}

	/* need to grab the location to store the status, as
	 * nfsv4 does some encoding while processing 
	 */
	nfserrp = rqstp->rq_res.head[0].iov_base
		+ rqstp->rq_res.head[0].iov_len;
	rqstp->rq_res.head[0].iov_len += sizeof(__be32);

	/* Now call the procedure handler, and encode NFS status. */
	nfserr = proc->pc_func(rqstp, rqstp->rq_argp, rqstp->rq_resp);
	nfserr = map_new_errors(rqstp->rq_vers, nfserr);
	if (nfserr == nfserr_dropit || rqstp->rq_dropme) {
		dprintk("nfsd: Dropping request; may be revisited later\n");
		nfsd_cache_update(rqstp, RC_NOCACHE, NULL);
		return 0;
	}

	if (rqstp->rq_proc != 0)
		*nfserrp++ = nfserr;

	/* Encode result.
	 * For NFSv2, additional info is never returned in case of an error.
	 */
	if (!(nfserr && rqstp->rq_vers == 2)) {
		xdr = proc->pc_encode;
		if (xdr && !xdr(rqstp, nfserrp,
				rqstp->rq_resp)) {
			/* Failed to encode result. Release cache entry */
			dprintk("nfsd: failed to encode result!\n");
			nfsd_cache_update(rqstp, RC_NOCACHE, NULL);
			*statp = rpc_system_err;
			return 1;
		}
	}

	/* Store reply in cache. */
	nfsd_cache_update(rqstp, rqstp->rq_cachetype, statp + 1);
	return 1;
}