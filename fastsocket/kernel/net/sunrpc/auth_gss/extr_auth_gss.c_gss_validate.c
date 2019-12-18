#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct xdr_netobj {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct xdr_buf {int dummy; } ;
struct rpc_task {int /*<<< orphan*/  tk_pid; TYPE_1__* tk_rqstp; } ;
struct rpc_cred {TYPE_2__* cr_auth; int /*<<< orphan*/  cr_flags; } ;
struct kvec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct gss_cl_ctx {int /*<<< orphan*/  gc_gss_ctx; } ;
typedef  int /*<<< orphan*/  seq ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int au_verfsize; } ;
struct TYPE_3__ {int /*<<< orphan*/  rq_seqno; struct rpc_cred* rq_cred; } ;

/* Variables and functions */
 scalar_t__ GSS_S_CONTEXT_EXPIRED ; 
 int /*<<< orphan*/  RPCAUTH_CRED_UPTODATE ; 
 scalar_t__ RPC_AUTH_GSS ; 
 scalar_t__ RPC_MAX_AUTH_SIZE ; 
 int XDR_QUADLEN (scalar_t__) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,...) ; 
 struct gss_cl_ctx* gss_cred_get_ctx (struct rpc_cred*) ; 
 int /*<<< orphan*/  gss_put_ctx (struct gss_cl_ctx*) ; 
 scalar_t__ gss_verify_mic (int /*<<< orphan*/ ,struct xdr_buf*,struct xdr_netobj*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_buf_from_iov (struct kvec*,struct xdr_buf*) ; 

__attribute__((used)) static __be32 *
gss_validate(struct rpc_task *task, __be32 *p)
{
	struct rpc_cred *cred = task->tk_rqstp->rq_cred;
	struct gss_cl_ctx *ctx = gss_cred_get_ctx(cred);
	__be32		seq;
	struct kvec	iov;
	struct xdr_buf	verf_buf;
	struct xdr_netobj mic;
	u32		flav,len;
	u32		maj_stat;

	dprintk("RPC: %5u gss_validate\n", task->tk_pid);

	flav = ntohl(*p++);
	if ((len = ntohl(*p++)) > RPC_MAX_AUTH_SIZE)
		goto out_bad;
	if (flav != RPC_AUTH_GSS)
		goto out_bad;
	seq = htonl(task->tk_rqstp->rq_seqno);
	iov.iov_base = &seq;
	iov.iov_len = sizeof(seq);
	xdr_buf_from_iov(&iov, &verf_buf);
	mic.data = (u8 *)p;
	mic.len = len;

	maj_stat = gss_verify_mic(ctx->gc_gss_ctx, &verf_buf, &mic);
	if (maj_stat == GSS_S_CONTEXT_EXPIRED)
		clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
	if (maj_stat) {
		dprintk("RPC: %5u gss_validate: gss_verify_mic returned "
				"error 0x%08x\n", task->tk_pid, maj_stat);
		goto out_bad;
	}
	/* We leave it to unwrap to calculate au_rslack. For now we just
	 * calculate the length of the verifier: */
	cred->cr_auth->au_verfsize = XDR_QUADLEN(len) + 2;
	gss_put_ctx(ctx);
	dprintk("RPC: %5u gss_validate: gss_verify_mic succeeded.\n",
			task->tk_pid);
	return p + XDR_QUADLEN(len);
out_bad:
	gss_put_ctx(ctx);
	dprintk("RPC: %5u gss_validate failed.\n", task->tk_pid);
	return NULL;
}