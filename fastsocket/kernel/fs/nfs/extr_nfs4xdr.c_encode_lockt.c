#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct nfs_lockt_args {int /*<<< orphan*/  lock_owner; TYPE_1__* fl; } ;
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  nops; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  fl_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_LOCKT ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ decode_lockt_maxsz ; 
 int /*<<< orphan*/  encode_lockowner (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_lock_length (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs4_lock_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_lockt(struct xdr_stream *xdr, const struct nfs_lockt_args *args, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 24);
	*p++ = cpu_to_be32(OP_LOCKT);
	*p++ = cpu_to_be32(nfs4_lock_type(args->fl, 0));
	p = xdr_encode_hyper(p, args->fl->fl_start);
	p = xdr_encode_hyper(p, nfs4_lock_length(args->fl));
	encode_lockowner(xdr, &args->lock_owner);
	hdr->nops++;
	hdr->replen += decode_lockt_maxsz;
}