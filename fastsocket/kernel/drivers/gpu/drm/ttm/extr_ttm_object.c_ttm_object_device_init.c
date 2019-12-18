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
struct ttm_object_device {int /*<<< orphan*/  object_hash; int /*<<< orphan*/  object_count; int /*<<< orphan*/  object_lock; struct ttm_mem_global* mem_glob; } ;
struct ttm_mem_global {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_ht_create (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct ttm_object_device*) ; 
 struct ttm_object_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct ttm_object_device *ttm_object_device_init(struct ttm_mem_global
						 *mem_glob,
						 unsigned int hash_order)
{
	struct ttm_object_device *tdev = kmalloc(sizeof(*tdev), GFP_KERNEL);
	int ret;

	if (unlikely(tdev == NULL))
		return NULL;

	tdev->mem_glob = mem_glob;
	rwlock_init(&tdev->object_lock);
	atomic_set(&tdev->object_count, 0);
	ret = drm_ht_create(&tdev->object_hash, hash_order);

	if (likely(ret == 0))
		return tdev;

	kfree(tdev);
	return NULL;
}