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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct xdr_netobj {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct xdr_buf {scalar_t__ len; struct kvec* head; struct kvec* tail; scalar_t__ page_len; } ;
struct rpc_rqst {scalar_t__ rq_seqno; struct xdr_buf rq_snd_buf; } ;
struct rpc_cred {int /*<<< orphan*/  cr_flags; } ;
struct kvec {int iov_len; void** iov_base; } ;
struct gss_cl_ctx {int /*<<< orphan*/  gc_gss_ctx; } ;
typedef  int (* kxdrproc_t ) (struct rpc_rqst*,void**,void*) ;
typedef  void* __be32 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ GSS_S_CONTEXT_EXPIRED ; 
 int /*<<< orphan*/  RPCAUTH_CRED_UPTODATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_get_mic (int /*<<< orphan*/ ,struct xdr_buf*,struct xdr_netobj*) ; 
 void* htonl (scalar_t__) ; 
 scalar_t__ xdr_buf_subsegment (struct xdr_buf*,struct xdr_buf*,scalar_t__,scalar_t__) ; 
 void** xdr_encode_opaque (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
gss_wrap_req_integ(struct rpc_cred *cred, struct gss_cl_ctx *ctx,
		kxdrproc_t encode, struct rpc_rqst *rqstp, __be32 *p, void *obj)
{
	struct xdr_buf	*snd_buf = &rqstp->rq_snd_buf;
	struct xdr_buf	integ_buf;
	__be32          *integ_len = NULL;
	struct xdr_netobj mic;
	u32		offset;
	__be32		*q;
	struct kvec	*iov;
	u32             maj_stat = 0;
	int		status = -EIO;

	integ_len = p++;
	offset = (u8 *)p - (u8 *)snd_buf->head[0].iov_base;
	*p++ = htonl(rqstp->rq_seqno);

	status = encode(rqstp, p, obj);
	if (status)
		return status;

	if (xdr_buf_subsegment(snd_buf, &integ_buf,
				offset, snd_buf->len - offset))
		return status;
	*integ_len = htonl(integ_buf.len);

	/* guess whether we're in the head or the tail: */
	if (snd_buf->page_len || snd_buf->tail[0].iov_len)
		iov = snd_buf->tail;
	else
		iov = snd_buf->head;
	p = iov->iov_base + iov->iov_len;
	mic.data = (u8 *)(p + 1);

	maj_stat = gss_get_mic(ctx->gc_gss_ctx, &integ_buf, &mic);
	status = -EIO; /* XXX? */
	if (maj_stat == GSS_S_CONTEXT_EXPIRED)
		clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
	else if (maj_stat)
		return status;
	q = xdr_encode_opaque(p, NULL, mic.len);

	offset = (u8 *)q - (u8 *)p;
	iov->iov_len += offset;
	snd_buf->len += offset;
	return 0;
}