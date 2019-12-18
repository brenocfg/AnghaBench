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
struct rpc_rqst {int /*<<< orphan*/  rq_snd_buf; } ;
struct nfs4_setclientid_res {int dummy; } ;
struct compound_hdr {int /*<<< orphan*/  nops; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  const FATTR4_WORD0_LEASE_TIME ; 
 int /*<<< orphan*/  encode_compound_hdr (struct xdr_stream*,struct rpc_rqst*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_fsinfo (struct xdr_stream*,int /*<<< orphan*/  const*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_nops (struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_putrootfh (struct xdr_stream*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_setclientid_confirm (struct xdr_stream*,struct nfs4_setclientid_res*,struct compound_hdr*) ; 
 int /*<<< orphan*/  xdr_init_encode (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_xdr_enc_setclientid_confirm(struct rpc_rqst *req, __be32 *p, struct nfs4_setclientid_res *arg)
{
	struct xdr_stream xdr;
	struct compound_hdr hdr = {
		.nops	= 0,
	};
	const u32 lease_bitmap[2] = { FATTR4_WORD0_LEASE_TIME, 0 };

	xdr_init_encode(&xdr, &req->rq_snd_buf, p);
	encode_compound_hdr(&xdr, req, &hdr);
	encode_setclientid_confirm(&xdr, arg, &hdr);
	encode_putrootfh(&xdr, &hdr);
	encode_fsinfo(&xdr, lease_bitmap, &hdr);
	encode_nops(&hdr);
	return 0;
}