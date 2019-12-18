#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {TYPE_2__* buf; TYPE_1__* iov; int /*<<< orphan*/ * p; int /*<<< orphan*/ * end; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {size_t len; } ;
struct TYPE_3__ {size_t iov_len; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__be32 * xdr_reserve_space(struct xdr_stream *xdr, size_t nbytes)
{
	__be32 *p = xdr->p;
	__be32 *q;

	/* align nbytes on the next 32-bit boundary */
	nbytes += 3;
	nbytes &= ~3;
	q = p + (nbytes >> 2);
	if (unlikely(q > xdr->end || q < p))
		return NULL;
	xdr->p = q;
	xdr->iov->iov_len += nbytes;
	xdr->buf->len += nbytes;
	return p;
}