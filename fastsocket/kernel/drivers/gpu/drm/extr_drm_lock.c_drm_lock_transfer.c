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
struct drm_lock_data {int /*<<< orphan*/ * file_priv; TYPE_1__* hw_lock; } ;
struct TYPE_2__ {unsigned int lock; } ;

/* Variables and functions */
 unsigned int _DRM_LOCK_HELD ; 
 unsigned int cmpxchg (unsigned int volatile*,unsigned int,unsigned int) ; 

__attribute__((used)) static int drm_lock_transfer(struct drm_lock_data *lock_data,
			     unsigned int context)
{
	unsigned int old, new, prev;
	volatile unsigned int *lock = &lock_data->hw_lock->lock;

	lock_data->file_priv = NULL;
	do {
		old = *lock;
		new = context | _DRM_LOCK_HELD;
		prev = cmpxchg(lock, old, new);
	} while (prev != old);
	return 1;
}