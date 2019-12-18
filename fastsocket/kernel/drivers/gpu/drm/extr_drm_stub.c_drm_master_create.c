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
struct drm_minor {int /*<<< orphan*/  master_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock_queue; int /*<<< orphan*/  spinlock; } ;
struct drm_master {int /*<<< orphan*/  head; struct drm_minor* minor; int /*<<< orphan*/  magicfree; int /*<<< orphan*/  magiclist; TYPE_1__ lock; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MAGIC_HASH_ORDER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_ht_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct drm_master* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct drm_master *drm_master_create(struct drm_minor *minor)
{
	struct drm_master *master;

	master = kzalloc(sizeof(*master), GFP_KERNEL);
	if (!master)
		return NULL;

	kref_init(&master->refcount);
	spin_lock_init(&master->lock.spinlock);
	init_waitqueue_head(&master->lock.lock_queue);
	drm_ht_create(&master->magiclist, DRM_MAGIC_HASH_ORDER);
	INIT_LIST_HEAD(&master->magicfree);
	master->minor = minor;

	list_add_tail(&master->head, &minor->master_list);

	return master;
}