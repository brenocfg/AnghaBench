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
struct xdr_stream {unsigned int nwords; int /*<<< orphan*/ * p; int /*<<< orphan*/ * end; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int XDR_QUADLEN (size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static __be32 * __xdr_inline_decode(struct xdr_stream *xdr, size_t nbytes)
{
	unsigned int nwords = XDR_QUADLEN(nbytes);
	__be32 *p = xdr->p;
	__be32 *q = p + nwords;

	if (unlikely(nwords > xdr->nwords || q > xdr->end || q < p))
		return NULL;
	xdr->p = q;
	xdr->nwords -= nwords;
	return p;
}