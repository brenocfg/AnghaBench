#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ daddr_t ;
typedef  TYPE_1__* blist_t ;
struct TYPE_3__ {scalar_t__ bl_radix; int /*<<< orphan*/  bl_free; int /*<<< orphan*/  bl_skip; int /*<<< orphan*/  bl_root; } ;

/* Variables and functions */
 scalar_t__ BLIST_BMAP_RADIX ; 
 scalar_t__ SWAPBLK_NONE ; 
 scalar_t__ blst_leaf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ blst_meta_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

daddr_t 
blist_alloc(blist_t bl, daddr_t count)
{
	daddr_t blk = SWAPBLK_NONE;

	if (bl) {
		if (bl->bl_radix == BLIST_BMAP_RADIX)
			blk = blst_leaf_alloc(bl->bl_root, 0, count);
		else
			blk = blst_meta_alloc(bl->bl_root, 0, count,
					      bl->bl_radix, bl->bl_skip);
		if (blk != SWAPBLK_NONE)
			bl->bl_free -= count;
	}
	return(blk);
}