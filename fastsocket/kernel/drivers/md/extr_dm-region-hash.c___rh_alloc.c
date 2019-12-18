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
struct dm_region_hash {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  region_lock; int /*<<< orphan*/  clean_regions; int /*<<< orphan*/  region_pool; TYPE_2__* log; } ;
struct dm_region {scalar_t__ state; int /*<<< orphan*/  list; int /*<<< orphan*/  delayed_bios; int /*<<< orphan*/  pending; int /*<<< orphan*/  key; struct dm_region_hash* rh; } ;
typedef  int /*<<< orphan*/  region_t ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {scalar_t__ (* in_sync ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ DM_RH_CLEAN ; 
 scalar_t__ DM_RH_NOSYNC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int GFP_NOIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  __rh_insert (struct dm_region_hash*,struct dm_region*) ; 
 struct dm_region* __rh_lookup (struct dm_region_hash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 struct dm_region* kmalloc (int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dm_region* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct dm_region*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dm_region *__rh_alloc(struct dm_region_hash *rh, region_t region)
{
	struct dm_region *reg, *nreg;

	nreg = mempool_alloc(rh->region_pool, GFP_ATOMIC);
	if (unlikely(!nreg))
		nreg = kmalloc(sizeof(*nreg), GFP_NOIO | __GFP_NOFAIL);

	nreg->state = rh->log->type->in_sync(rh->log, region, 1) ?
		      DM_RH_CLEAN : DM_RH_NOSYNC;
	nreg->rh = rh;
	nreg->key = region;
	INIT_LIST_HEAD(&nreg->list);
	atomic_set(&nreg->pending, 0);
	bio_list_init(&nreg->delayed_bios);

	write_lock_irq(&rh->hash_lock);
	reg = __rh_lookup(rh, region);
	if (reg)
		/* We lost the race. */
		mempool_free(nreg, rh->region_pool);
	else {
		__rh_insert(rh, nreg);
		if (nreg->state == DM_RH_CLEAN) {
			spin_lock(&rh->region_lock);
			list_add(&nreg->list, &rh->clean_regions);
			spin_unlock(&rh->region_lock);
		}

		reg = nreg;
	}
	write_unlock_irq(&rh->hash_lock);

	return reg;
}