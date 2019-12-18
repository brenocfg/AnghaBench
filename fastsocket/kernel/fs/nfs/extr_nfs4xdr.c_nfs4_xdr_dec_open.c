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
struct nfs_openres {int /*<<< orphan*/  server; int /*<<< orphan*/  f_attr; int /*<<< orphan*/  access_result; int /*<<< orphan*/  access_supported; scalar_t__ access_request; int /*<<< orphan*/  fh; int /*<<< orphan*/  seq_res; } ;
struct compound_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ decode_access (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int /*<<< orphan*/  decode_getfattr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ decode_getfh (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int decode_open (struct xdr_stream*,struct nfs_openres*) ; 
 int decode_putfh (struct xdr_stream*) ; 
 int decode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct rpc_rqst*) ; 
 int /*<<< orphan*/  xdr_init_decode (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_xdr_dec_open(struct rpc_rqst *rqstp, __be32 *p, struct nfs_openres *res)
{
	struct xdr_stream xdr;
	struct compound_hdr hdr;
	int status;

	xdr_init_decode(&xdr, &rqstp->rq_rcv_buf, p);
	status = decode_compound_hdr(&xdr, &hdr);
	if (status)
		goto out;
	status = decode_sequence(&xdr, &res->seq_res, rqstp);
	if (status)
		goto out;
	status = decode_putfh(&xdr);
	if (status)
		goto out;
	status = decode_open(&xdr, res);
	if (status)
		goto out;
	if (decode_getfh(&xdr, &res->fh) != 0)
		goto out;
	if (res->access_request &&
	    decode_access(&xdr, &res->access_supported, &res->access_result) != 0)
		goto out;
	decode_getfattr(&xdr, res->f_attr, res->server);
out:
	return status;
}