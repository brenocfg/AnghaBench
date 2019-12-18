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
struct bio {int bi_max_vecs; int /*<<< orphan*/  bi_destructor; struct bio_vec* bi_io_vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bio_init (struct bio*) ; 
 struct bio_vec* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bio*) ; 
 struct bio* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_bio_destructor ; 

__attribute__((used)) static struct bio *pkt_bio_alloc(int nr_iovecs)
{
	struct bio_vec *bvl = NULL;
	struct bio *bio;

	bio = kmalloc(sizeof(struct bio), GFP_KERNEL);
	if (!bio)
		goto no_bio;
	bio_init(bio);

	bvl = kcalloc(nr_iovecs, sizeof(struct bio_vec), GFP_KERNEL);
	if (!bvl)
		goto no_bvl;

	bio->bi_max_vecs = nr_iovecs;
	bio->bi_io_vec = bvl;
	bio->bi_destructor = pkt_bio_destructor;

	return bio;

 no_bvl:
	kfree(bio);
 no_bio:
	return NULL;
}