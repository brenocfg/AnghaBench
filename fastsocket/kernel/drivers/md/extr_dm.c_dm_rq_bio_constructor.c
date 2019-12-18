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
struct mapped_device {int dummy; } ;
struct dm_rq_target_io {struct mapped_device* md; } ;
struct dm_rq_clone_bio_info {struct dm_rq_target_io* tio; struct bio* orig; } ;
struct bio {int /*<<< orphan*/  bi_destructor; struct dm_rq_clone_bio_info* bi_private; int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dm_rq_clone_bio_info* alloc_bio_info (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_rq_bio_destructor ; 
 int /*<<< orphan*/  end_clone_bio ; 

__attribute__((used)) static int dm_rq_bio_constructor(struct bio *bio, struct bio *bio_orig,
				 void *data)
{
	struct dm_rq_target_io *tio = data;
	struct mapped_device *md = tio->md;
	struct dm_rq_clone_bio_info *info = alloc_bio_info(md);

	if (!info)
		return -ENOMEM;

	info->orig = bio_orig;
	info->tio = tio;
	bio->bi_end_io = end_clone_bio;
	bio->bi_private = info;
	bio->bi_destructor = dm_rq_bio_destructor;

	return 0;
}