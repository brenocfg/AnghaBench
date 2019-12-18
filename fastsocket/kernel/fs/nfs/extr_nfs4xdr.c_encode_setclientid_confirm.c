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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct nfs4_setclientid_res {TYPE_1__ confirm; int /*<<< orphan*/  clientid; } ;
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  nops; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ NFS4_VERIFIER_SIZE ; 
 int /*<<< orphan*/  OP_SETCLIENTID_CONFIRM ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ decode_setclientid_confirm_maxsz ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,scalar_t__) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void encode_setclientid_confirm(struct xdr_stream *xdr, const struct nfs4_setclientid_res *arg, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 12 + NFS4_VERIFIER_SIZE);
	*p++ = cpu_to_be32(OP_SETCLIENTID_CONFIRM);
	p = xdr_encode_hyper(p, arg->clientid);
	xdr_encode_opaque_fixed(p, arg->confirm.data, NFS4_VERIFIER_SIZE);
	hdr->nops++;
	hdr->replen += decode_setclientid_confirm_maxsz;
}