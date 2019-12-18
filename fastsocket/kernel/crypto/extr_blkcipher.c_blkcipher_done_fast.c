#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ virt; } ;
struct blkcipher_walk {int flags; int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  page; TYPE_2__ dst; } ;

/* Variables and functions */
 int BLKCIPHER_WALK_COPY ; 
 int BLKCIPHER_WALK_DIFF ; 
 int BLKCIPHER_WALK_PHYS ; 
 int /*<<< orphan*/  blkcipher_map_dst (struct blkcipher_walk*) ; 
 int /*<<< orphan*/  blkcipher_unmap_dst (struct blkcipher_walk*) ; 
 int /*<<< orphan*/  blkcipher_unmap_src (struct blkcipher_walk*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_advance (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline unsigned int blkcipher_done_fast(struct blkcipher_walk *walk,
					       unsigned int n)
{
	if (walk->flags & BLKCIPHER_WALK_COPY) {
		blkcipher_map_dst(walk);
		memcpy(walk->dst.virt.addr, walk->page, n);
		blkcipher_unmap_dst(walk);
	} else if (!(walk->flags & BLKCIPHER_WALK_PHYS)) {
		if (walk->flags & BLKCIPHER_WALK_DIFF)
			blkcipher_unmap_dst(walk);
		blkcipher_unmap_src(walk);
	}

	scatterwalk_advance(&walk->in, n);
	scatterwalk_advance(&walk->out, n);

	return n;
}