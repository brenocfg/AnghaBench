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
typedef  int uint32_t ;
struct xdr_stream {int dummy; } ;
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  nops; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int OP_GETATTR ; 
 void* cpu_to_be32 (int) ; 
 scalar_t__ decode_getattr_maxsz ; 
 void** reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_getattr_two(struct xdr_stream *xdr, uint32_t bm0, uint32_t bm1, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 16);
	*p++ = cpu_to_be32(OP_GETATTR);
	*p++ = cpu_to_be32(2);
	*p++ = cpu_to_be32(bm0);
	*p = cpu_to_be32(bm1);
	hdr->nops++;
	hdr->replen += decode_getattr_maxsz;
}