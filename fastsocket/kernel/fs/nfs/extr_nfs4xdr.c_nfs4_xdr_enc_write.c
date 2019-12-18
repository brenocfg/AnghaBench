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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct rpc_rqst {TYPE_1__ rq_snd_buf; } ;
struct nfs_writeargs {int /*<<< orphan*/  bitmask; int /*<<< orphan*/  fh; int /*<<< orphan*/  seq_args; } ;
struct compound_hdr {int /*<<< orphan*/  minorversion; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  XDRBUF_WRITE ; 
 int /*<<< orphan*/  encode_compound_hdr (struct xdr_stream*,struct rpc_rqst*,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_getfattr (struct xdr_stream*,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_nops (struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_putfh (struct xdr_stream*,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_sequence (struct xdr_stream*,int /*<<< orphan*/ *,struct compound_hdr*) ; 
 int /*<<< orphan*/  encode_write (struct xdr_stream*,struct nfs_writeargs*,struct compound_hdr*) ; 
 int /*<<< orphan*/  nfs4_xdr_minorversion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_init_encode (struct xdr_stream*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_xdr_enc_write(struct rpc_rqst *req, __be32 *p, struct nfs_writeargs *args)
{
	struct xdr_stream xdr;
	struct compound_hdr hdr = {
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	};

	xdr_init_encode(&xdr, &req->rq_snd_buf, p);
	encode_compound_hdr(&xdr, req, &hdr);
	encode_sequence(&xdr, &args->seq_args, &hdr);
	encode_putfh(&xdr, args->fh, &hdr);
	encode_write(&xdr, args, &hdr);
	req->rq_snd_buf.flags |= XDRBUF_WRITE;
	if (args->bitmask)
		encode_getfattr(&xdr, args->bitmask, &hdr);
	encode_nops(&hdr);
	return 0;
}