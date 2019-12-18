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
struct origin {struct block_device* bdev; int /*<<< orphan*/  snapshots; } ;
struct dm_snapshot {TYPE_1__* origin; } ;
struct block_device {int dummy; } ;
struct TYPE_2__ {struct block_device* bdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __insert_origin (struct origin*) ; 
 int /*<<< orphan*/  __insert_snapshot (struct origin*,struct dm_snapshot*) ; 
 struct origin* __lookup_origin (struct block_device*) ; 
 int __validate_exception_handover (struct dm_snapshot*) ; 
 int /*<<< orphan*/  _origins_lock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct origin*) ; 
 struct origin* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int register_snapshot(struct dm_snapshot *snap)
{
	struct origin *o, *new_o = NULL;
	struct block_device *bdev = snap->origin->bdev;
	int r = 0;

	new_o = kmalloc(sizeof(*new_o), GFP_KERNEL);
	if (!new_o)
		return -ENOMEM;

	down_write(&_origins_lock);

	r = __validate_exception_handover(snap);
	if (r < 0) {
		kfree(new_o);
		goto out;
	}

	o = __lookup_origin(bdev);
	if (o)
		kfree(new_o);
	else {
		/* New origin */
		o = new_o;

		/* Initialise the struct */
		INIT_LIST_HEAD(&o->snapshots);
		o->bdev = bdev;

		__insert_origin(o);
	}

	__insert_snapshot(o, snap);

out:
	up_write(&_origins_lock);

	return r;
}