#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct crypto_blkcipher {int dummy; } ;
struct TYPE_11__ {int offset; void* page; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {TYPE_5__ phys; TYPE_2__ virt; } ;
struct TYPE_9__ {int offset; void* page; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {TYPE_3__ phys; TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int total; int flags; unsigned int nbytes; TYPE_6__ dst; TYPE_4__ src; int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  blocksize; void* page; } ;
struct blkcipher_desc {int /*<<< orphan*/  flags; struct crypto_blkcipher* tfm; } ;

/* Variables and functions */
 int BLKCIPHER_WALK_COPY ; 
 int BLKCIPHER_WALK_DIFF ; 
 int BLKCIPHER_WALK_PHYS ; 
 int BLKCIPHER_WALK_SLOW ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_BLOCK_LEN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int blkcipher_next_copy (struct blkcipher_walk*) ; 
 int blkcipher_next_fast (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 int blkcipher_next_slow (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int,unsigned int) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,int /*<<< orphan*/ ) ; 
 unsigned int crypto_blkcipher_alignmask (struct crypto_blkcipher*) ; 
 unsigned int crypto_blkcipher_blocksize (struct crypto_blkcipher*) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_aligned (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int scatterwalk_clamp (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 void* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blkcipher_walk_next(struct blkcipher_desc *desc,
			       struct blkcipher_walk *walk)
{
	struct crypto_blkcipher *tfm = desc->tfm;
	unsigned int alignmask = crypto_blkcipher_alignmask(tfm);
	unsigned int bsize;
	unsigned int n;
	int err;

	n = walk->total;
	if (unlikely(n < crypto_blkcipher_blocksize(tfm))) {
		desc->flags |= CRYPTO_TFM_RES_BAD_BLOCK_LEN;
		return blkcipher_walk_done(desc, walk, -EINVAL);
	}

	walk->flags &= ~(BLKCIPHER_WALK_SLOW | BLKCIPHER_WALK_COPY |
			 BLKCIPHER_WALK_DIFF);
	if (!scatterwalk_aligned(&walk->in, alignmask) ||
	    !scatterwalk_aligned(&walk->out, alignmask)) {
		walk->flags |= BLKCIPHER_WALK_COPY;
		if (!walk->page) {
			walk->page = (void *)__get_free_page(GFP_ATOMIC);
			if (!walk->page)
				n = 0;
		}
	}

	bsize = min(walk->blocksize, n);
	n = scatterwalk_clamp(&walk->in, n);
	n = scatterwalk_clamp(&walk->out, n);

	if (unlikely(n < bsize)) {
		err = blkcipher_next_slow(desc, walk, bsize, alignmask);
		goto set_phys_lowmem;
	}

	walk->nbytes = n;
	if (walk->flags & BLKCIPHER_WALK_COPY) {
		err = blkcipher_next_copy(walk);
		goto set_phys_lowmem;
	}

	return blkcipher_next_fast(desc, walk);

set_phys_lowmem:
	if (walk->flags & BLKCIPHER_WALK_PHYS) {
		walk->src.phys.page = virt_to_page(walk->src.virt.addr);
		walk->dst.phys.page = virt_to_page(walk->dst.virt.addr);
		walk->src.phys.offset &= PAGE_SIZE - 1;
		walk->dst.phys.offset &= PAGE_SIZE - 1;
	}
	return err;
}