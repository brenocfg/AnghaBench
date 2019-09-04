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
typedef  int daddr_t ;
struct TYPE_4__ {int bmu_bitmap; } ;
struct TYPE_5__ {int bm_bighint; TYPE_1__ u; } ;
typedef  TYPE_2__ blmeta_t ;

/* Variables and functions */
 int BLIST_BMAP_RADIX ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
blst_leaf_free(blmeta_t *scan, daddr_t blk, int count)
{
	/*
	 * free some data in this bitmap
	 *
	 * e.g.
	 *	0000111111111110000
	 *          \_________/\__/
	 *		v        n
	 */
	int n = blk & (BLIST_BMAP_RADIX - 1);
	u_daddr_t mask;

	mask = ((u_daddr_t)-1 << n) &
	    ((u_daddr_t)-1 >> (BLIST_BMAP_RADIX - count - n));

	if (scan->u.bmu_bitmap & mask)
		panic("blst_radix_free: freeing free block");
	scan->u.bmu_bitmap |= mask;

	/*
	 * We could probably do a better job here.  We are required to make
	 * bighint at least as large as the biggest contiguous block of 
	 * data.  If we just shoehorn it, a little extra overhead will
	 * be incured on the next allocation (but only that one typically).
	 */
	scan->bm_bighint = BLIST_BMAP_RADIX;
}