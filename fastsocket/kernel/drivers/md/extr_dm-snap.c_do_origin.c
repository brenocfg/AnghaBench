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
struct origin {int /*<<< orphan*/  snapshots; } ;
struct dm_dev {int /*<<< orphan*/  bdev; } ;
struct bio {int /*<<< orphan*/  bi_sector; } ;

/* Variables and functions */
 int DM_MAPIO_REMAPPED ; 
 struct origin* __lookup_origin (int /*<<< orphan*/ ) ; 
 int __origin_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  _origins_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_origin(struct dm_dev *origin, struct bio *bio)
{
	struct origin *o;
	int r = DM_MAPIO_REMAPPED;

	down_read(&_origins_lock);
	o = __lookup_origin(origin->bdev);
	if (o)
		r = __origin_write(&o->snapshots, bio->bi_sector, bio);
	up_read(&_origins_lock);

	return r;
}