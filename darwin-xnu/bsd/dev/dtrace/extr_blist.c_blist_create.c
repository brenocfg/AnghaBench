#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct blist {int dummy; } ;
typedef  int daddr_t ;
typedef  int /*<<< orphan*/  blmeta_t ;
typedef  TYPE_1__* blist_t ;
struct TYPE_4__ {int bl_blocks; int bl_radix; int bl_skip; int bl_rootblks; int /*<<< orphan*/ * bl_root; } ;

/* Variables and functions */
 int BLIST_BMAP_RADIX ; 
 int BLIST_META_RADIX_SHIFT ; 
 int /*<<< orphan*/  M_SWAP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int blst_radix_init (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

blist_t 
blist_create(daddr_t blocks)
{
	blist_t bl;
	int radix;
	int skip = 0;

	/*
	 * Calculate radix and skip field used for scanning.
	 */
	radix = BLIST_BMAP_RADIX;

	while (radix < blocks) {
		radix <<= BLIST_META_RADIX_SHIFT;
		skip = (skip + 1) << BLIST_META_RADIX_SHIFT;
	}

	bl = malloc(sizeof(struct blist), M_SWAP, M_WAITOK);

	bzero(bl, sizeof(*bl));

	bl->bl_blocks = blocks;
	bl->bl_radix = radix;
	bl->bl_skip = skip;
	bl->bl_rootblks = 1 +
	    blst_radix_init(NULL, bl->bl_radix, bl->bl_skip, blocks);
	bl->bl_root = malloc(sizeof(blmeta_t) * bl->bl_rootblks, M_SWAP, M_WAITOK);

#if defined(BLIST_DEBUG)
	printf(
		"BLIST representing %d blocks (%d MB of swap)"
		", requiring %dK of ram\n",
		bl->bl_blocks,
		bl->bl_blocks * 4 / 1024,
		(bl->bl_rootblks * sizeof(blmeta_t) + 1023) / 1024
	);
	printf("BLIST raw radix tree contains %d records\n", bl->bl_rootblks);
#endif
	blst_radix_init(bl->bl_root, bl->bl_radix, bl->bl_skip, blocks);

	return(bl);
}