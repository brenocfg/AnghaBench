#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int daddr_t ;
struct TYPE_5__ {scalar_t__ bmu_avail; scalar_t__ bmu_bitmap; } ;
struct TYPE_6__ {int bm_bighint; TYPE_1__ u; } ;
typedef  TYPE_2__ blmeta_t ;

/* Variables and functions */
 int BLIST_META_RADIX_SHIFT ; 
 int /*<<< orphan*/  blst_leaf_free (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

__attribute__((used)) static void 
blst_meta_free(blmeta_t *scan, daddr_t freeBlk, daddr_t count, daddr_t radix,
	       int skip, daddr_t blk)
{
	int i;
	int next_skip = (skip >> BLIST_META_RADIX_SHIFT);

#if 0
	printf("FREE (%x,%d) FROM (%x,%d)\n",
	    freeBlk, count,
	    blk, radix
	);
#endif

	if (scan->u.bmu_avail == 0) {
		/*
		 * ALL-ALLOCATED special case, with possible
		 * shortcut to ALL-FREE special case.
		 */
		scan->u.bmu_avail = count;
		scan->bm_bighint = count;

		if (count != radix)  {
			for (i = 1; i <= skip; i += next_skip) {
				if (scan[i].bm_bighint == (daddr_t)-1)
					break;
				scan[i].bm_bighint = 0;
				if (next_skip == 1)
					scan[i].u.bmu_bitmap = 0;
				else
					scan[i].u.bmu_avail = 0;
			}
			/* fall through */
		}
	} else {
		scan->u.bmu_avail += count;
		/* scan->bm_bighint = radix; */
	}

	/*
	 * ALL-FREE special case.
	 */

	if (scan->u.bmu_avail == radix)
		return;
	if (scan->u.bmu_avail > radix)
		panic("blst_meta_free: freeing already free blocks (%d) %d/%d", count, scan->u.bmu_avail, radix);

	/*
	 * Break the free down into its components
	 */

	radix >>= BLIST_META_RADIX_SHIFT;

	i = (freeBlk - blk) / radix;
	blk += i * radix;
	i = i * next_skip + 1;

	while (i <= skip && blk < freeBlk + count) {
		daddr_t v;

		v = blk + radix - freeBlk;
		if (v > count)
			v = count;

		if (scan->bm_bighint == (daddr_t)-1)
			panic("blst_meta_free: freeing unexpected range");

		if (next_skip == 1)
			blst_leaf_free(&scan[i], freeBlk, v);
		else
			blst_meta_free(&scan[i], freeBlk, v, radix,
				       next_skip - 1, blk);
		if (scan->bm_bighint < scan[i].bm_bighint)
		    scan->bm_bighint = scan[i].bm_bighint;
		count -= v;
		freeBlk += v;
		blk += radix;
		i += next_skip;
	}
}