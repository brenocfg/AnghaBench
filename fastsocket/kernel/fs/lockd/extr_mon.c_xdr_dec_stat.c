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
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_rcv_buf; } ;
struct nsm_res {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_init_decode (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int xdr_dec_stat(struct rpc_rqst *rqstp, __be32 *p,
			struct nsm_res *resp)
{
	struct xdr_stream xdr;

	xdr_init_decode(&xdr, &rqstp->rq_rcv_buf, p);
	p = xdr_inline_decode(&xdr, sizeof(u32));
	if (unlikely(p == NULL))
		return -EIO;
	resp->state = ntohl(*p);

	dprintk("lockd: xdr_dec_stat state %d\n", resp->state);
	return 0;
}