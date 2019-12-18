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
struct video_device_shadow {int /*<<< orphan*/  fh_lock; } ;
struct v4l2_kevent {int /*<<< orphan*/  list; } ;
struct v4l2_fh {int /*<<< orphan*/  vdev; struct v4l2_events* events; } ;
struct v4l2_events {unsigned int nallocated; int /*<<< orphan*/  free; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct v4l2_kevent* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct video_device_shadow* video_device_shadow_get (int /*<<< orphan*/ ) ; 

int v4l2_event_alloc(struct v4l2_fh *fh, unsigned int n)
{
	struct v4l2_events *events = fh->events;
	unsigned long flags;
	struct video_device_shadow *shvdev = video_device_shadow_get(fh->vdev);

	if (!events || !shvdev) {
		WARN_ON(1);
		return -ENOMEM;
	}

	while (events->nallocated < n) {
		struct v4l2_kevent *kev;

		kev = kzalloc(sizeof(*kev), GFP_KERNEL);
		if (kev == NULL)
			return -ENOMEM;

		spin_lock_irqsave(&shvdev->fh_lock, flags);
		list_add_tail(&kev->list, &events->free);
		events->nallocated++;
		spin_unlock_irqrestore(&shvdev->fh_lock, flags);
	}

	return 0;
}