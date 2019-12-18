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
struct multipath {int queue_io; struct dm_target* ti; int /*<<< orphan*/  mpio_pool; int /*<<< orphan*/  work_mutex; int /*<<< orphan*/  pg_init_wait; int /*<<< orphan*/  trigger_event; int /*<<< orphan*/  process_queued_ios; int /*<<< orphan*/  pg_init_delay_msecs; int /*<<< orphan*/  lock; int /*<<< orphan*/  queued_ios; int /*<<< orphan*/  priority_groups; } ;
struct dm_target {struct multipath* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_PG_INIT_DELAY_DEFAULT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_IOS ; 
 int /*<<< orphan*/  _mpio_cache ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct multipath*) ; 
 struct multipath* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_create_slab_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_queued_ios ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trigger_event ; 

__attribute__((used)) static struct multipath *alloc_multipath(struct dm_target *ti)
{
	struct multipath *m;

	m = kzalloc(sizeof(*m), GFP_KERNEL);
	if (m) {
		INIT_LIST_HEAD(&m->priority_groups);
		INIT_LIST_HEAD(&m->queued_ios);
		spin_lock_init(&m->lock);
		m->queue_io = 1;
		m->pg_init_delay_msecs = DM_PG_INIT_DELAY_DEFAULT;
		INIT_WORK(&m->process_queued_ios, process_queued_ios);
		INIT_WORK(&m->trigger_event, trigger_event);
		init_waitqueue_head(&m->pg_init_wait);
		mutex_init(&m->work_mutex);
		m->mpio_pool = mempool_create_slab_pool(MIN_IOS, _mpio_cache);
		if (!m->mpio_pool) {
			kfree(m);
			return NULL;
		}
		m->ti = ti;
		ti->private = m;
	}

	return m;
}