#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct svc_version {int vs_nproc; int /*<<< orphan*/  (* vs_dispatch ) (struct svc_rqst*,scalar_t__*) ;struct svc_procedure* vs_proc; } ;
struct svc_serv {TYPE_2__* sv_stats; struct svc_program* sv_program; } ;
struct svc_rqst {int rq_splice_ok; int rq_usedeferral; int rq_dropme; int rq_prog; int rq_vers; int rq_proc; int /*<<< orphan*/  rq_resp; int /*<<< orphan*/  rq_argp; struct svc_procedure* rq_procinfo; TYPE_3__* rq_xprt; int /*<<< orphan*/  rq_xid; struct svc_serv* rq_server; } ;
struct svc_program {int pg_prog; int (* pg_authenticate ) (struct svc_rqst*) ;int pg_nvers; int pg_lovers; int pg_hivers; int /*<<< orphan*/  pg_name; struct svc_version** pg_vers; struct svc_program* pg_next; } ;
struct svc_procedure {scalar_t__ (* pc_func ) (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int pc_xdrressize; int /*<<< orphan*/  (* pc_encode ) (struct svc_rqst*,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pc_release ) (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pc_decode ) (struct svc_rqst*,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pc_ressize; int /*<<< orphan*/  pc_argsize; int /*<<< orphan*/  pc_count; } ;
struct kvec {int iov_len; void* iov_base; } ;
typedef  int /*<<< orphan*/  (* kxdrproc_t ) (struct svc_rqst*,void*,int /*<<< orphan*/ ) ;
typedef  scalar_t__ __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  xpt_flags; TYPE_1__* xpt_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  rpcbadfmt; int /*<<< orphan*/  rpcbadauth; int /*<<< orphan*/  rpccnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* xpo_prep_reply_hdr ) (struct svc_rqst*) ;} ;

/* Variables and functions */
 int RPC_PROC_UNAVAIL ; 
 int RPC_PROG_MISMATCH ; 
 int RPC_PROG_UNAVAIL ; 
 int RPC_SUCCESS ; 
#define  SVC_CLOSE 134 
#define  SVC_COMPLETE 133 
#define  SVC_DENIED 132 
#define  SVC_DROP 131 
#define  SVC_GARBAGE 130 
#define  SVC_OK 129 
#define  SVC_SYSERR 128 
 int /*<<< orphan*/  XPT_TEMP ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohl (scalar_t__) ; 
 scalar_t__ rpc_autherr_badcred ; 
 scalar_t__ rpc_garbage_args ; 
 scalar_t__ rpc_success ; 
 scalar_t__ rpc_system_err ; 
 int /*<<< orphan*/  stub1 (struct svc_rqst*) ; 
 int stub2 (struct svc_rqst*) ; 
 scalar_t__ stub3 (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct svc_rqst*,scalar_t__*) ; 
 int /*<<< orphan*/  stub6 (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int svc_authenticate (struct svc_rqst*,scalar_t__*) ; 
 scalar_t__ svc_authorise (struct svc_rqst*) ; 
 int /*<<< orphan*/  svc_close_xprt (TYPE_3__*) ; 
 int svc_getnl (struct kvec*) ; 
 int /*<<< orphan*/  svc_printk (struct svc_rqst*,char*,...) ; 
 int /*<<< orphan*/  svc_putnl (struct kvec*,int) ; 
 int /*<<< orphan*/  svc_putu32 (struct kvec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_reserve_auth (struct svc_rqst*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_ressize_check (struct svc_rqst*,scalar_t__*) ; 

__attribute__((used)) static int
svc_process_common(struct svc_rqst *rqstp, struct kvec *argv, struct kvec *resv)
{
	struct svc_program	*progp;
	struct svc_version	*versp = NULL;	/* compiler food */
	struct svc_procedure	*procp = NULL;
	struct svc_serv		*serv = rqstp->rq_server;
	kxdrproc_t		xdr;
	__be32			*statp;
	u32			prog, vers, proc;
	__be32			auth_stat, rpc_stat;
	int			auth_res;
	__be32			*reply_statp;

	rpc_stat = rpc_success;

	if (argv->iov_len < 6*4)
		goto err_short_len;

	/* Will be turned off only in gss privacy case: */
	rqstp->rq_splice_ok = 1;
	/* Will be turned off only when NFSv4 Sessions are used */
	rqstp->rq_usedeferral = 1;
	rqstp->rq_dropme = false;

	/* Setup reply header */
	rqstp->rq_xprt->xpt_ops->xpo_prep_reply_hdr(rqstp);

	svc_putu32(resv, rqstp->rq_xid);

	vers = svc_getnl(argv);

	/* First words of reply: */
	svc_putnl(resv, 1);		/* REPLY */

	if (vers != 2)		/* RPC version number */
		goto err_bad_rpc;

	/* Save position in case we later decide to reject: */
	reply_statp = resv->iov_base + resv->iov_len;

	svc_putnl(resv, 0);		/* ACCEPT */

	rqstp->rq_prog = prog = svc_getnl(argv);	/* program number */
	rqstp->rq_vers = vers = svc_getnl(argv);	/* version number */
	rqstp->rq_proc = proc = svc_getnl(argv);	/* procedure number */

	progp = serv->sv_program;

	for (progp = serv->sv_program; progp; progp = progp->pg_next)
		if (prog == progp->pg_prog)
			break;

	/*
	 * Decode auth data, and add verifier to reply buffer.
	 * We do this before anything else in order to get a decent
	 * auth verifier.
	 */
	auth_res = svc_authenticate(rqstp, &auth_stat);
	/* Also give the program a chance to reject this call: */
	if (auth_res == SVC_OK && progp) {
		auth_stat = rpc_autherr_badcred;
		auth_res = progp->pg_authenticate(rqstp);
	}
	switch (auth_res) {
	case SVC_OK:
		break;
	case SVC_GARBAGE:
		goto err_garbage;
	case SVC_SYSERR:
		rpc_stat = rpc_system_err;
		goto err_bad;
	case SVC_DENIED:
		goto err_bad_auth;
	case SVC_CLOSE:
		if (test_bit(XPT_TEMP, &rqstp->rq_xprt->xpt_flags))
			svc_close_xprt(rqstp->rq_xprt);
	case SVC_DROP:
		goto dropit;
	case SVC_COMPLETE:
		goto sendit;
	}

	if (progp == NULL)
		goto err_bad_prog;

	if (vers >= progp->pg_nvers ||
	  !(versp = progp->pg_vers[vers]))
		goto err_bad_vers;

	procp = versp->vs_proc + proc;
	if (proc >= versp->vs_nproc || !procp->pc_func)
		goto err_bad_proc;
	rqstp->rq_procinfo = procp;

	/* Syntactic check complete */
	serv->sv_stats->rpccnt++;

	/* Build the reply header. */
	statp = resv->iov_base +resv->iov_len;
	svc_putnl(resv, RPC_SUCCESS);

	/* Bump per-procedure stats counter */
	procp->pc_count++;

	/* Initialize storage for argp and resp */
	memset(rqstp->rq_argp, 0, procp->pc_argsize);
	memset(rqstp->rq_resp, 0, procp->pc_ressize);

	/* un-reserve some of the out-queue now that we have a
	 * better idea of reply size
	 */
	if (procp->pc_xdrressize)
		svc_reserve_auth(rqstp, procp->pc_xdrressize<<2);

	/* Call the function that processes the request. */
	if (!versp->vs_dispatch) {
		/* Decode arguments */
		xdr = procp->pc_decode;
		if (xdr && !xdr(rqstp, argv->iov_base, rqstp->rq_argp))
			goto err_garbage;

		*statp = procp->pc_func(rqstp, rqstp->rq_argp, rqstp->rq_resp);

		/* Encode reply */
		if (rqstp->rq_dropme) {
			if (procp->pc_release)
				procp->pc_release(rqstp, NULL, rqstp->rq_resp);
			goto dropit;
		}
		if (*statp == rpc_success && (xdr = procp->pc_encode)
		 && !xdr(rqstp, resv->iov_base+resv->iov_len, rqstp->rq_resp)) {
			dprintk("svc: failed to encode reply\n");
			/* serv->sv_stats->rpcsystemerr++; */
			*statp = rpc_system_err;
		}
	} else {
		dprintk("svc: calling dispatcher\n");
		if (!versp->vs_dispatch(rqstp, statp)) {
			/* Release reply info */
			if (procp->pc_release)
				procp->pc_release(rqstp, NULL, rqstp->rq_resp);
			goto dropit;
		}
	}

	/* Check RPC status result */
	if (*statp != rpc_success)
		resv->iov_len = ((void*)statp)  - resv->iov_base + 4;

	/* Release reply info */
	if (procp->pc_release)
		procp->pc_release(rqstp, NULL, rqstp->rq_resp);

	if (procp->pc_encode == NULL)
		goto dropit;

 sendit:
	if (svc_authorise(rqstp))
		goto dropit;
	return 1;		/* Caller can now send it */

 dropit:
	svc_authorise(rqstp);	/* doesn't hurt to call this twice */
	dprintk("svc: svc_process dropit\n");
	return 0;

err_short_len:
	svc_printk(rqstp, "short len %Zd, dropping request\n",
			argv->iov_len);

	goto dropit;			/* drop request */

err_bad_rpc:
	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, 1);	/* REJECT */
	svc_putnl(resv, 0);	/* RPC_MISMATCH */
	svc_putnl(resv, 2);	/* Only RPCv2 supported */
	svc_putnl(resv, 2);
	goto sendit;

err_bad_auth:
	dprintk("svc: authentication failed (%d)\n", ntohl(auth_stat));
	serv->sv_stats->rpcbadauth++;
	/* Restore write pointer to location of accept status: */
	xdr_ressize_check(rqstp, reply_statp);
	svc_putnl(resv, 1);	/* REJECT */
	svc_putnl(resv, 1);	/* AUTH_ERROR */
	svc_putnl(resv, ntohl(auth_stat));	/* status */
	goto sendit;

err_bad_prog:
	dprintk("svc: unknown program %d\n", prog);
	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, RPC_PROG_UNAVAIL);
	goto sendit;

err_bad_vers:
	svc_printk(rqstp, "unknown version (%d for prog %d, %s)\n",
		       vers, prog, progp->pg_name);

	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, RPC_PROG_MISMATCH);
	svc_putnl(resv, progp->pg_lovers);
	svc_putnl(resv, progp->pg_hivers);
	goto sendit;

err_bad_proc:
	svc_printk(rqstp, "unknown procedure (%d)\n", proc);

	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, RPC_PROC_UNAVAIL);
	goto sendit;

err_garbage:
	svc_printk(rqstp, "failed to decode args\n");

	rpc_stat = rpc_garbage_args;
err_bad:
	serv->sv_stats->rpcbadfmt++;
	svc_putnl(resv, ntohl(rpc_stat));
	goto sendit;
}