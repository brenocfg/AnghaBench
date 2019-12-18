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
struct ttm_object_device {int /*<<< orphan*/  object_lock; } ;
struct ttm_base_object {int /*<<< orphan*/  refcount; TYPE_1__* tfile; } ;
struct TYPE_2__ {struct ttm_object_device* tdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_release_base ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void ttm_base_object_unref(struct ttm_base_object **p_base)
{
	struct ttm_base_object *base = *p_base;
	struct ttm_object_device *tdev = base->tfile->tdev;

	*p_base = NULL;

	/*
	 * Need to take the lock here to avoid racing with
	 * users trying to look up the object.
	 */

	write_lock(&tdev->object_lock);
	kref_put(&base->refcount, ttm_release_base);
	write_unlock(&tdev->object_lock);
}