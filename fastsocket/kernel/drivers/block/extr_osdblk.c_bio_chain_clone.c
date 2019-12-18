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
struct bio {struct bio* bi_next; int /*<<< orphan*/ * bi_bdev; int /*<<< orphan*/  bi_max_vecs; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSDBLK_DEBUG (char*) ; 
 int /*<<< orphan*/  __GFP_WAIT ; 
 int /*<<< orphan*/  __bio_clone (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  bio_chain_put (struct bio*) ; 
 struct bio* bio_kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bio *bio_chain_clone(struct bio *old_chain, gfp_t gfpmask)
{
	struct bio *tmp, *new_chain = NULL, *tail = NULL;

	while (old_chain) {
		tmp = bio_kmalloc(gfpmask, old_chain->bi_max_vecs);
		if (!tmp)
			goto err_out;

		__bio_clone(tmp, old_chain);
		tmp->bi_bdev = NULL;
		gfpmask &= ~__GFP_WAIT;
		tmp->bi_next = NULL;

		if (!new_chain)
			new_chain = tail = tmp;
		else {
			tail->bi_next = tmp;
			tail = tmp;
		}

		old_chain = old_chain->bi_next;
	}

	return new_chain;

err_out:
	OSDBLK_DEBUG("bio_chain_clone with err\n");
	bio_chain_put(new_chain);
	return NULL;
}