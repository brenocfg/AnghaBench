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
struct bio_vec {int dummy; } ;
struct bio_set {unsigned int front_pad; int /*<<< orphan*/  bio_pool; int /*<<< orphan*/  bio_slab; } ;

/* Variables and functions */
 int BIO_INLINE_VECS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bio_find_or_create_slab (unsigned int) ; 
 int /*<<< orphan*/  bioset_free (struct bio_set*) ; 
 int /*<<< orphan*/  biovec_create_pools (struct bio_set*,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct bio_set*) ; 
 struct bio_set* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_create_slab_pool (unsigned int,int /*<<< orphan*/ ) ; 

struct bio_set *bioset_create(unsigned int pool_size, unsigned int front_pad)
{
	unsigned int back_pad = BIO_INLINE_VECS * sizeof(struct bio_vec);
	struct bio_set *bs;

	bs = kzalloc(sizeof(*bs), GFP_KERNEL);
	if (!bs)
		return NULL;

	bs->front_pad = front_pad;

	bs->bio_slab = bio_find_or_create_slab(front_pad + back_pad);
	if (!bs->bio_slab) {
		kfree(bs);
		return NULL;
	}

	bs->bio_pool = mempool_create_slab_pool(pool_size, bs->bio_slab);
	if (!bs->bio_pool)
		goto bad;

	if (!biovec_create_pools(bs, pool_size))
		return bs;

bad:
	bioset_free(bs);
	return NULL;
}