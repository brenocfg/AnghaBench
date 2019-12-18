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
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int FUSE_MAX_PAGES_PER_REQ ; 
 unsigned long PAGE_MASK ; 
 size_t PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 unsigned long fuse_get_user_addr (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,size_t) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 size_t iov_iter_single_seg_count (struct iov_iter*) ; 
 int min (int,int) ; 

__attribute__((used)) static inline int fuse_iter_npages(const struct iov_iter *ii_p)
{
	struct iov_iter ii = *ii_p;
	int npages = 0;

	while (iov_iter_count(&ii) && npages < FUSE_MAX_PAGES_PER_REQ) {
		unsigned long user_addr = fuse_get_user_addr(&ii);
		unsigned offset = user_addr & ~PAGE_MASK;
		size_t frag_size = iov_iter_single_seg_count(&ii);

		npages += (frag_size + offset + PAGE_SIZE - 1) >> PAGE_SHIFT;
		iov_iter_advance(&ii, frag_size);
	}

	return min(npages, FUSE_MAX_PAGES_PER_REQ);
}