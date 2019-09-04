#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_daddr_t ;
typedef  scalar_t__ daddr_t ;
struct TYPE_4__ {int bmu_bitmap; } ;
struct TYPE_5__ {int bm_bighint; TYPE_1__ u; } ;
typedef  TYPE_2__ blmeta_t ;

/* Variables and functions */
 int BLIST_BMAP_RADIX ; 
 scalar_t__ SWAPBLK_NONE ; 

__attribute__((used)) static daddr_t
blst_leaf_alloc(blmeta_t *scan, daddr_t blk, int count)
{
	u_daddr_t orig = scan->u.bmu_bitmap;

	if (orig == 0) {
		/*
		 * Optimize bitmap all-allocated case.  Also, count = 1
		 * case assumes at least 1 bit is free in the bitmap, so
		 * we have to take care of this case here.
		 */
		scan->bm_bighint = 0;
		return(SWAPBLK_NONE);
	}
	if (count == 1) {
		/*
		 * Optimized code to allocate one bit out of the bitmap
		 */
		u_daddr_t mask;
		int j = BLIST_BMAP_RADIX/2;
		int r = 0;

		mask = (u_daddr_t)-1 >> (BLIST_BMAP_RADIX/2);

		while (j) {
			if ((orig & mask) == 0) {
			    r += j;
			    orig >>= j;
			}
			j >>= 1;
			mask >>= j;
		}
		scan->u.bmu_bitmap &= ~(1 << r);
		return(blk + r);
	}
#if !defined(__APPLE__)
	if (count <= BLIST_BMAP_RADIX) {
#else
	if (count <= (int)BLIST_BMAP_RADIX) {
#endif /* __APPLE__ */
		/*
		 * non-optimized code to allocate N bits out of the bitmap.
		 * The more bits, the faster the code runs.  It will run
		 * the slowest allocating 2 bits, but since there aren't any
		 * memory ops in the core loop (or shouldn't be, anyway),
		 * you probably won't notice the difference.
		 */
		int j;
		int n = BLIST_BMAP_RADIX - count;
		u_daddr_t mask;

		mask = (u_daddr_t)-1 >> n;

		for (j = 0; j <= n; ++j) {
			if ((orig & mask) == mask) {
				scan->u.bmu_bitmap &= ~mask;
				return(blk + j);
			}
			mask = (mask << 1);
		}
	}
	/*
	 * We couldn't allocate count in this subtree, update bighint.
	 */
	scan->bm_bighint = count - 1;
	return(SWAPBLK_NONE);
}