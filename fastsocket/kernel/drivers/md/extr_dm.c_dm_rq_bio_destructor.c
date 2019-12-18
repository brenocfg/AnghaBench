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
struct mapped_device {int /*<<< orphan*/  bs; } ;
struct dm_rq_clone_bio_info {TYPE_1__* tio; } ;
struct bio {struct dm_rq_clone_bio_info* bi_private; } ;
struct TYPE_2__ {struct mapped_device* md; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_free (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_bio_info (struct dm_rq_clone_bio_info*) ; 

__attribute__((used)) static void dm_rq_bio_destructor(struct bio *bio)
{
	struct dm_rq_clone_bio_info *info = bio->bi_private;
	struct mapped_device *md = info->tio->md;

	free_bio_info(info);
	bio_free(bio, md->bs);
}