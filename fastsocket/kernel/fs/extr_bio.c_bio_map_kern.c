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
struct bio {unsigned int bi_size; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct bio* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct bio*) ; 
 struct bio* __bio_map_kern (struct request_queue*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 

struct bio *bio_map_kern(struct request_queue *q, void *data, unsigned int len,
			 gfp_t gfp_mask)
{
	struct bio *bio;

	bio = __bio_map_kern(q, data, len, gfp_mask);
	if (IS_ERR(bio))
		return bio;

	if (bio->bi_size == len)
		return bio;

	/*
	 * Don't support partial mappings.
	 */
	bio_put(bio);
	return ERR_PTR(-EINVAL);
}