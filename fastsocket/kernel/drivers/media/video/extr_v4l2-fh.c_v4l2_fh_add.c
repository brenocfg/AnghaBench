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
struct video_device_shadow {int /*<<< orphan*/  fh_lock; int /*<<< orphan*/  fh_list; } ;
struct v4l2_fh {int /*<<< orphan*/  list; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct video_device_shadow* video_device_shadow_get (int /*<<< orphan*/ ) ; 

void v4l2_fh_add(struct v4l2_fh *fh)
{
	unsigned long flags;
	struct video_device_shadow *shvdev = video_device_shadow_get(fh->vdev);

	spin_lock_irqsave(&shvdev->fh_lock, flags);
	list_add(&fh->list, &shvdev->fh_list);
	spin_unlock_irqrestore(&shvdev->fh_lock, flags);
}