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
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_rcv_buf; } ;
struct nfs4_fs_locations_res {TYPE_1__* fs_locations; int /*<<< orphan*/  seq_res; } ;
struct compound_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  server; int /*<<< orphan*/  fattr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int decode_compound_hdr (struct xdr_stream*,struct compound_hdr*) ; 
 int decode_getfattr (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int decode_lookup (struct xdr_stream*) ; 
 int decode_putfh (struct xdr_stream*) ; 
 int decode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct rpc_rqst*) ; 
 int /*<<< orphan*/  xdr_enter_page (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_init_decode (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_xdr_dec_fs_locations(struct rpc_rqst *req, __be32 *p,
				     struct nfs4_fs_locations_res *res)
{
	struct xdr_stream xdr;
	struct compound_hdr hdr;
	int status;

	xdr_init_decode(&xdr, &req->rq_rcv_buf, p);
	status = decode_compound_hdr(&xdr, &hdr);
	if (status)
		goto out;
	status = decode_sequence(&xdr, &res->seq_res, req);
	if (status)
		goto out;
	if ((status = decode_putfh(&xdr)) != 0)
		goto out;
	if ((status = decode_lookup(&xdr)) != 0)
		goto out;
	xdr_enter_page(&xdr, PAGE_SIZE);
	status = decode_getfattr(&xdr, &res->fs_locations->fattr,
				 res->fs_locations->server);
out:
	return status;
}