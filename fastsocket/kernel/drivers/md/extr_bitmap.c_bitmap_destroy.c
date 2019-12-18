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
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct mddev {TYPE_2__* thread; TYPE_1__ bitmap_info; struct bitmap* bitmap; } ;
struct bitmap {scalar_t__ sysfs_can_clear; } ;
struct TYPE_4__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  bitmap_free (struct bitmap*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_put (scalar_t__) ; 

void bitmap_destroy(struct mddev *mddev)
{
	struct bitmap *bitmap = mddev->bitmap;

	if (!bitmap) /* there was no bitmap */
		return;

	mutex_lock(&mddev->bitmap_info.mutex);
	mddev->bitmap = NULL; /* disconnect from the md device */
	mutex_unlock(&mddev->bitmap_info.mutex);
	if (mddev->thread)
		mddev->thread->timeout = MAX_SCHEDULE_TIMEOUT;

	if (bitmap->sysfs_can_clear)
		sysfs_put(bitmap->sysfs_can_clear);

	bitmap_free(bitmap);
}