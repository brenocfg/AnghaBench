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
struct pool {int dummy; } ;
struct dm_bio_prison_cell {int dummy; } ;
struct bio_list {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  cell_error (struct pool*,struct dm_bio_prison_cell*) ; 
 int /*<<< orphan*/  cell_release (struct pool*,struct dm_bio_prison_cell*,struct bio_list*) ; 
 int /*<<< orphan*/  retry_on_resume (struct bio*) ; 
 scalar_t__ should_error_unserviceable_bio (struct pool*) ; 

__attribute__((used)) static void retry_bios_on_resume(struct pool *pool, struct dm_bio_prison_cell *cell)
{
	struct bio *bio;
	struct bio_list bios;

	if (should_error_unserviceable_bio(pool)) {
		cell_error(pool, cell);
		return;
	}

	bio_list_init(&bios);
	cell_release(pool, cell, &bios);

	if (should_error_unserviceable_bio(pool))
		while ((bio = bio_list_pop(&bios)))
			bio_io_error(bio);
	else
		while ((bio = bio_list_pop(&bios)))
			retry_on_resume(bio);
}