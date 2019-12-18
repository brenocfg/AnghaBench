#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_region_hash {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  region_lock; TYPE_2__* log; } ;
struct dm_region {scalar_t__ state; int /*<<< orphan*/  key; int /*<<< orphan*/  list; int /*<<< orphan*/  pending; } ;
typedef  int /*<<< orphan*/  region_t ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mark_region ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ DM_RH_CLEAN ; 
 scalar_t__ DM_RH_DIRTY ; 
 struct dm_region* __rh_find (struct dm_region_hash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void dm_rh_inc(struct dm_region_hash *rh, region_t region)
{
	struct dm_region *reg;

	read_lock(&rh->hash_lock);
	reg = __rh_find(rh, region);

	spin_lock_irq(&rh->region_lock);
	atomic_inc(&reg->pending);

	if (reg->state == DM_RH_CLEAN) {
		reg->state = DM_RH_DIRTY;
		list_del_init(&reg->list);	/* take off the clean list */
		spin_unlock_irq(&rh->region_lock);

		rh->log->type->mark_region(rh->log, reg->key);
	} else
		spin_unlock_irq(&rh->region_lock);


	read_unlock(&rh->hash_lock);
}