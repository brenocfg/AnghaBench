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
struct dm_deferred_set {TYPE_1__* entries; scalar_t__ sweeper; scalar_t__ current_entry; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  work_items; scalar_t__ count; struct dm_deferred_set* ds; } ;

/* Variables and functions */
 int DEFERRED_SET_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct dm_deferred_set* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct dm_deferred_set *dm_deferred_set_create(void)
{
	int i;
	struct dm_deferred_set *ds;

	ds = kmalloc(sizeof(*ds), GFP_KERNEL);
	if (!ds)
		return NULL;

	spin_lock_init(&ds->lock);
	ds->current_entry = 0;
	ds->sweeper = 0;
	for (i = 0; i < DEFERRED_SET_SIZE; i++) {
		ds->entries[i].ds = ds;
		ds->entries[i].count = 0;
		INIT_LIST_HEAD(&ds->entries[i].work_items);
	}

	return ds;
}