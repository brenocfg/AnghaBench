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
struct nfs_fsinfo {int dummy; } ;
struct compound_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int decode_fsinfo (struct xdr_stream*,struct nfs_fsinfo*) ; 
 int decode_putrootfh (struct xdr_stream*) ; 
 int decode_setclientid_confirm (struct xdr_stream*) ; 
 int /*<<< orphan*/  xdr_init_decode (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_xdr_dec_setclientid_confirm(struct rpc_rqst *req, __be32 *p, struct nfs_fsinfo *fsinfo)
{
	struct xdr_stream xdr;
	struct compound_hdr hdr;
	int status;

	xdr_init_decode(&xdr, &req->rq_rcv_buf, p);
	status = decode_compound_hdr(&xdr, &hdr);
	if (!status)
		status = decode_setclientid_confirm(&xdr);
	if (!status)
		status = decode_putrootfh(&xdr);
	if (!status)
		status = decode_fsinfo(&xdr, fsinfo);
	return status;
}