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
struct iovec {size_t iov_len; size_t iov_base; } ;

/* Variables and functions */
 size_t min (size_t,size_t) ; 

__attribute__((used)) static int move_iovec_hdr(struct iovec *from, struct iovec *to,
			  size_t len, int iov_count)
{
	int seg = 0;
	size_t size;
	while (len && seg < iov_count) {
		size = min(from->iov_len, len);
		to->iov_base = from->iov_base;
		to->iov_len = size;
		from->iov_len -= size;
		from->iov_base += size;
		len -= size;
		++from;
		++to;
		++seg;
	}
	return seg;
}