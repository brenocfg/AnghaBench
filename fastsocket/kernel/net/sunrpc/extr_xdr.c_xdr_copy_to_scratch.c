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
struct TYPE_2__ {size_t iov_len; int /*<<< orphan*/ * iov_base; } ;
struct xdr_stream {TYPE_1__ scratch; int /*<<< orphan*/ * p; scalar_t__ end; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * __xdr_inline_decode (struct xdr_stream*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  xdr_set_next_buffer (struct xdr_stream*) ; 

__attribute__((used)) static __be32 *xdr_copy_to_scratch(struct xdr_stream *xdr, size_t nbytes)
{
	__be32 *p;
	void *cpdest = xdr->scratch.iov_base;
	size_t cplen = (char *)xdr->end - (char *)xdr->p;

	if (nbytes > xdr->scratch.iov_len)
		return NULL;
	memcpy(cpdest, xdr->p, cplen);
	cpdest += cplen;
	nbytes -= cplen;
	if (!xdr_set_next_buffer(xdr))
		return NULL;
	p = __xdr_inline_decode(xdr, nbytes);
	if (p == NULL)
		return NULL;
	memcpy(cpdest, p, nbytes);
	return xdr->scratch.iov_base;
}