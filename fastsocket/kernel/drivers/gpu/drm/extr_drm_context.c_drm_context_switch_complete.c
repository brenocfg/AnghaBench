#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_file {TYPE_3__* master; } ;
struct drm_device {int last_context; int /*<<< orphan*/  context_wait; int /*<<< orphan*/  context_flag; int /*<<< orphan*/  last_switch; } ;
struct TYPE_5__ {TYPE_1__* hw_lock; } ;
struct TYPE_6__ {TYPE_2__ lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  _DRM_LOCK_IS_HELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_context_switch_complete(struct drm_device *dev,
				       struct drm_file *file_priv, int new)
{
	dev->last_context = new;	/* PRE/POST: This is the _only_ writer. */
	dev->last_switch = jiffies;

	if (!_DRM_LOCK_IS_HELD(file_priv->master->lock.hw_lock->lock)) {
		DRM_ERROR("Lock isn't held after context switch\n");
	}

	/* If a context switch is ever initiated
	   when the kernel holds the lock, release
	   that lock here. */
	clear_bit(0, &dev->context_flag);
	wake_up(&dev->context_wait);

	return 0;
}