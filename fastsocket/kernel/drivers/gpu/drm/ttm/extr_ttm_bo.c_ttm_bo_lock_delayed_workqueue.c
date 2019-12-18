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
struct ttm_bo_device {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

int ttm_bo_lock_delayed_workqueue(struct ttm_bo_device *bdev)
{
	return cancel_delayed_work_sync(&bdev->wq);
}