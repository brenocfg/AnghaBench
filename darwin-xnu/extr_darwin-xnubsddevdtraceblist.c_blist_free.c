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
 int /*<<< orphan*/  blst_leaf_free (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  blst_meta_free (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
blist_free(blist_t bl, daddr_t blkno, daddr_t count)
{
	if (bl) {
		if (bl->bl_radix == BLIST_BMAP_RADIX)
			blst_leaf_free(bl->bl_root, blkno, count);
		else
			blst_meta_free(bl->bl_root, blkno, count,
				       bl->bl_radix, bl->bl_skip, 0);
		bl->bl_free += count;
	}
}