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
struct bio_set {int dummy; } ;
struct bio_integrity_payload {int bip_vcnt; int /*<<< orphan*/  bip_idx; int /*<<< orphan*/  bip_sector; int /*<<< orphan*/  bip_vec; } ;
struct bio {struct bio_integrity_payload* bi_integrity; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
 struct bio_integrity_payload* bio_integrity_alloc_bioset (struct bio*,int /*<<< orphan*/ ,int,struct bio_set*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int bio_integrity_clone(struct bio *bio, struct bio *bio_src,
			gfp_t gfp_mask, struct bio_set *bs)
{
	struct bio_integrity_payload *bip_src = bio_src->bi_integrity;
	struct bio_integrity_payload *bip;

	BUG_ON(bip_src == NULL);

	bip = bio_integrity_alloc_bioset(bio, gfp_mask, bip_src->bip_vcnt, bs);

	if (bip == NULL)
		return -EIO;

	memcpy(bip->bip_vec, bip_src->bip_vec,
	       bip_src->bip_vcnt * sizeof(struct bio_vec));

	bip->bip_sector = bip_src->bip_sector;
	bip->bip_vcnt = bip_src->bip_vcnt;
	bip->bip_idx = bip_src->bip_idx;

	return 0;
}