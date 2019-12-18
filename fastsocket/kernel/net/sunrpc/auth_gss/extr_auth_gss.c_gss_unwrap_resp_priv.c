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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct xdr_buf {scalar_t__ len; TYPE_1__* head; } ;
struct rpc_rqst {scalar_t__ rq_seqno; struct xdr_buf rq_rcv_buf; } ;
struct rpc_cred {int /*<<< orphan*/  cr_flags; } ;
struct gss_cl_ctx {int /*<<< orphan*/  gc_gss_ctx; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_CONTEXT_EXPIRED ; 
 int /*<<< orphan*/  RPCAUTH_CRED_UPTODATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_unwrap (int /*<<< orphan*/ ,scalar_t__,struct xdr_buf*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
gss_unwrap_resp_priv(struct rpc_cred *cred, struct gss_cl_ctx *ctx,
		struct rpc_rqst *rqstp, __be32 **p)
{
	struct xdr_buf  *rcv_buf = &rqstp->rq_rcv_buf;
	u32 offset;
	u32 opaque_len;
	u32 maj_stat;
	int status = -EIO;

	opaque_len = ntohl(*(*p)++);
	offset = (u8 *)(*p) - (u8 *)rcv_buf->head[0].iov_base;
	if (offset + opaque_len > rcv_buf->len)
		return status;
	/* remove padding: */
	rcv_buf->len = offset + opaque_len;

	maj_stat = gss_unwrap(ctx->gc_gss_ctx, offset, rcv_buf);
	if (maj_stat == GSS_S_CONTEXT_EXPIRED)
		clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
	if (maj_stat != GSS_S_COMPLETE)
		return status;
	if (ntohl(*(*p)++) != rqstp->rq_seqno)
		return status;

	return 0;
}