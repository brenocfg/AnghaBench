#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct crypto_blkcipher {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sg; } ;
struct blkcipher_walk {int /*<<< orphan*/ * page; TYPE_1__ out; TYPE_1__ in; scalar_t__ iv; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  total; int /*<<< orphan*/  nbytes; } ;
struct blkcipher_desc {scalar_t__ info; struct crypto_blkcipher* tfm; } ;

/* Variables and functions */
 int EDEADLK ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int blkcipher_copy_iv (struct blkcipher_walk*,struct crypto_blkcipher*,unsigned int) ; 
 int blkcipher_walk_next (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 unsigned int crypto_blkcipher_alignmask (struct crypto_blkcipher*) ; 
 int /*<<< orphan*/  in_irq () ; 
 int /*<<< orphan*/  scatterwalk_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static int blkcipher_walk_first(struct blkcipher_desc *desc,
				struct blkcipher_walk *walk)
{
	struct crypto_blkcipher *tfm = desc->tfm;
	unsigned int alignmask = crypto_blkcipher_alignmask(tfm);

	if (WARN_ON_ONCE(in_irq()))
		return -EDEADLK;

	walk->nbytes = walk->total;
	if (unlikely(!walk->total))
		return 0;

	walk->buffer = NULL;
	walk->iv = desc->info;
	if (unlikely(((unsigned long)walk->iv & alignmask))) {
		int err = blkcipher_copy_iv(walk, tfm, alignmask);
		if (err)
			return err;
	}

	scatterwalk_start(&walk->in, walk->in.sg);
	scatterwalk_start(&walk->out, walk->out.sg);
	walk->page = NULL;

	return blkcipher_walk_next(desc, walk);
}