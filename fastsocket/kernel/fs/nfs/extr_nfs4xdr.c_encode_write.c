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
struct nfs_writeargs {int /*<<< orphan*/  count; int /*<<< orphan*/  pgbase; int /*<<< orphan*/  pages; int /*<<< orphan*/  stable; int /*<<< orphan*/  offset; TYPE_1__ stateid; } ;
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  nops; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_STATEID_SIZE ; 
 int /*<<< orphan*/  OP_WRITE ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ decode_write_maxsz ; 
 int /*<<< orphan*/  encode_opaque_fixed (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void** reserve_space (struct xdr_stream*,int) ; 
 void** xdr_encode_hyper (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_write_pages (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_write(struct xdr_stream *xdr, const struct nfs_writeargs *args, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(OP_WRITE);

	encode_opaque_fixed(xdr, args->stateid.data, NFS4_STATEID_SIZE);

	p = reserve_space(xdr, 16);
	p = xdr_encode_hyper(p, args->offset);
	*p++ = cpu_to_be32(args->stable);
	*p = cpu_to_be32(args->count);

	xdr_write_pages(xdr, args->pages, args->pgbase, args->count);
	hdr->nops++;
	hdr->replen += decode_write_maxsz;
}