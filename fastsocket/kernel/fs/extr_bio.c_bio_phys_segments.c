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
struct request_queue {int dummy; } ;
struct bio {int bi_phys_segments; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_SEG_VALID ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_recount_segments (struct request_queue*,struct bio*) ; 
 scalar_t__ unlikely (int) ; 

inline int bio_phys_segments(struct request_queue *q, struct bio *bio)
{
	if (unlikely(!bio_flagged(bio, BIO_SEG_VALID)))
		blk_recount_segments(q, bio);

	return bio->bi_phys_segments;
}