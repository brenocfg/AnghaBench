#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct nfs_closeargs {TYPE_3__* stateid; TYPE_2__* seqid; } ;
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  nops; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__* sequence; } ;
struct TYPE_4__ {int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 scalar_t__ NFS4_STATEID_SIZE ; 
 int /*<<< orphan*/  OP_CLOSE ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ decode_close_maxsz ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,scalar_t__) ; 
 int /*<<< orphan*/  xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void encode_close(struct xdr_stream *xdr, const struct nfs_closeargs *arg, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 8+NFS4_STATEID_SIZE);
	*p++ = cpu_to_be32(OP_CLOSE);
	*p++ = cpu_to_be32(arg->seqid->sequence->counter);
	xdr_encode_opaque_fixed(p, arg->stateid->data, NFS4_STATEID_SIZE);
	hdr->nops++;
	hdr->replen += decode_close_maxsz;
}