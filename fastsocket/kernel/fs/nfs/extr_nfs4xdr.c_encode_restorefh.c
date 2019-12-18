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
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  nops; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  OP_RESTOREFH ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ decode_restorefh_maxsz ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void
encode_restorefh(struct xdr_stream *xdr, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(OP_RESTOREFH);
	hdr->nops++;
	hdr->replen += decode_restorefh_maxsz;
}