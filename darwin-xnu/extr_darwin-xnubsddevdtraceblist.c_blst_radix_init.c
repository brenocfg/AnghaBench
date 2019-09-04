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
typedef  int daddr_t ;
struct TYPE_4__ {scalar_t__ bmu_avail; scalar_t__ bmu_bitmap; } ;
struct TYPE_5__ {int bm_bighint; TYPE_1__ u; } ;
typedef  TYPE_2__ blmeta_t ;

/* Variables and functions */
 int BLIST_BMAP_RADIX ; 
 int BLIST_META_RADIX_SHIFT ; 

__attribute__((used)) static daddr_t	
blst_radix_init(blmeta_t *scan, daddr_t radix, int skip, daddr_t count)
{
	int i;
	int next_skip;
	daddr_t memindex = 0;

	/*
	 * Leaf node
	 */

	if (radix == BLIST_BMAP_RADIX) {
		if (scan) {
			scan->bm_bighint = 0;
			scan->u.bmu_bitmap = 0;
		}
		return(memindex);
	}

	/*
	 * Meta node.  If allocating the entire object we can special
	 * case it.  However, we need to figure out how much memory
	 * is required to manage 'count' blocks, so we continue on anyway.
	 */

	if (scan) {
		scan->bm_bighint = 0;
		scan->u.bmu_avail = 0;
	}

	radix >>= BLIST_META_RADIX_SHIFT;
	next_skip = (skip >> BLIST_META_RADIX_SHIFT);

	for (i = 1; i <= skip; i += next_skip) {
		if (count >= radix) {
			/*
			 * Allocate the entire object
			 */
			memindex = i + blst_radix_init(
			    ((scan) ? &scan[i] : NULL),
			    radix,
			    next_skip - 1,
			    radix
			);
			count -= radix;
		} else if (count > 0) {
			/*
			 * Allocate a partial object
			 */
			memindex = i + blst_radix_init(
			    ((scan) ? &scan[i] : NULL),
			    radix,
			    next_skip - 1,
			    count
			);
			count = 0;
		} else {
			/*
			 * Add terminator and break out
			 */
			if (scan)
				scan[i].bm_bighint = (daddr_t)-1;
			break;
		}
	}
	if (memindex < i)
		memindex = i;
	return(memindex);
}