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
struct nfs_commitargs {int /*<<< orphan*/  count; int /*<<< orphan*/  offset; } ;
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  nops; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  OP_COMMIT ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ decode_commit_maxsz ; 
 void** reserve_space (struct xdr_stream*,int) ; 
 void** xdr_encode_hyper (void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_commit(struct xdr_stream *xdr, const struct nfs_commitargs *args, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 16);
	*p++ = cpu_to_be32(OP_COMMIT);
	p = xdr_encode_hyper(p, args->offset);
	*p = cpu_to_be32(args->count);
	hdr->nops++;
	hdr->replen += decode_commit_maxsz;
}