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
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_rcv_buf; } ;
struct mountres {scalar_t__ errno; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ EBADHANDLE ; 
 int decode_auth_flavors (struct xdr_stream*,struct mountres*) ; 
 int decode_fhandle3 (struct xdr_stream*,struct mountres*) ; 
 int decode_fhs_status (struct xdr_stream*,struct mountres*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdr_init_decode (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mnt_dec_mountres3(struct rpc_rqst *req, __be32 *p,
			     struct mountres *res)
{
	struct xdr_stream xdr;
	int status;

	xdr_init_decode(&xdr, &req->rq_rcv_buf, p);

	status = decode_fhs_status(&xdr, res);
	if (unlikely(status != 0 || res->errno != 0))
		return status;
	status = decode_fhandle3(&xdr, res);
	if (unlikely(status != 0)) {
		res->errno = -EBADHANDLE;
		return 0;
	}
	return decode_auth_flavors(&xdr, res);
}