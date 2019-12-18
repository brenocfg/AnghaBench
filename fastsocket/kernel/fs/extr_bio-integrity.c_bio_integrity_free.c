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
struct bio_set {int /*<<< orphan*/  bio_integrity_pool; } ;
struct bio_integrity_payload {size_t bip_slab; int /*<<< orphan*/ * bip_buf; } ;
struct bio {struct bio_integrity_payload* bi_integrity; } ;
struct TYPE_2__ {int /*<<< orphan*/  slab; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CLONED ; 
 int /*<<< orphan*/  BIO_FS_INTEGRITY ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 TYPE_1__* bip_slab ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct bio_integrity_payload*) ; 
 int /*<<< orphan*/  mempool_free (struct bio_integrity_payload*,int /*<<< orphan*/ ) ; 
 scalar_t__ use_bip_pool (size_t) ; 

void bio_integrity_free(struct bio *bio, struct bio_set *bs)
{
	struct bio_integrity_payload *bip = bio->bi_integrity;

	BUG_ON(bip == NULL);

	/* A cloned bio doesn't own the integrity metadata */
	if (!bio_flagged(bio, BIO_CLONED) && !bio_flagged(bio, BIO_FS_INTEGRITY)
	    && bip->bip_buf != NULL)
		kfree(bip->bip_buf);

	if (use_bip_pool(bip->bip_slab))
		mempool_free(bip, bs->bio_integrity_pool);
	else
		kmem_cache_free(bip_slab[bip->bip_slab].slab, bip);

	bio->bi_integrity = NULL;
}