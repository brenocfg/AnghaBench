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
struct blkcipher_walk {int /*<<< orphan*/  blocksize; int /*<<< orphan*/  flags; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKCIPHER_WALK_PHYS ; 
 int blkcipher_walk_first (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 int /*<<< orphan*/  crypto_blkcipher_blocksize (int /*<<< orphan*/ ) ; 

int blkcipher_walk_phys(struct blkcipher_desc *desc,
			struct blkcipher_walk *walk)
{
	walk->flags |= BLKCIPHER_WALK_PHYS;
	walk->blocksize = crypto_blkcipher_blocksize(desc->tfm);
	return blkcipher_walk_first(desc, walk);
}