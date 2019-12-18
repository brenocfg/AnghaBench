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
struct nfs_getaclres {int /*<<< orphan*/  seq_res; int /*<<< orphan*/ * acl_scratch; } ;
struct compound_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int decode_getacl (struct xdr_stream*,struct rpc_rqst*,struct nfs_getaclres*) ; 
 int decode_putfh (struct xdr_stream*) ; 
 int decode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct rpc_rqst*) ; 
 void* page_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_init_decode (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_set_scratch_buffer (struct xdr_stream*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs4_xdr_dec_getacl(struct rpc_rqst *rqstp, __be32 *p,
		    struct nfs_getaclres *res)
{
	struct xdr_stream xdr;
	struct compound_hdr hdr;
	int status;

	xdr_init_decode(&xdr, &rqstp->rq_rcv_buf, p);
	if (res->acl_scratch != NULL) {
		void *p = page_address(res->acl_scratch);
		xdr_set_scratch_buffer(&xdr, p, PAGE_SIZE);
	}
	status = decode_compound_hdr(&xdr, &hdr);
	if (status)
		goto out;
	status = decode_sequence(&xdr, &res->seq_res, rqstp);
	if (status)
		goto out;
	status = decode_putfh(&xdr);
	if (status)
		goto out;
	status = decode_getacl(&xdr, rqstp, res);

out:
	return status;
}