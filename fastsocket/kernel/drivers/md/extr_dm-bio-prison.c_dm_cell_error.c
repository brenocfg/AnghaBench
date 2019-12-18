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
struct dm_bio_prison_cell {int dummy; } ;
struct dm_bio_prison {int /*<<< orphan*/  lock; } ;
struct bio_list {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cell_release (struct dm_bio_prison_cell*,struct bio_list*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dm_cell_error(struct dm_bio_prison *prison,
		   struct dm_bio_prison_cell *cell)
{
	struct bio_list bios;
	struct bio *bio;
	unsigned long flags;

	bio_list_init(&bios);

	spin_lock_irqsave(&prison->lock, flags);
	__cell_release(cell, &bios);
	spin_unlock_irqrestore(&prison->lock, flags);

	while ((bio = bio_list_pop(&bios)))
		bio_io_error(bio);
}