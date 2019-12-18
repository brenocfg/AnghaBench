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
struct video_device_shadow {scalar_t__ lock; } ;
struct v4l2_fh {int /*<<< orphan*/  vdev; struct v4l2_events* events; } ;
struct v4l2_events {scalar_t__ navailable; int /*<<< orphan*/  wait; } ;
struct v4l2_event {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int __v4l2_event_dequeue (struct v4l2_fh*,struct v4l2_event*) ; 
 int /*<<< orphan*/  mutex_lock (scalar_t__) ; 
 int /*<<< orphan*/  mutex_unlock (scalar_t__) ; 
 struct video_device_shadow* video_device_shadow_get (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int v4l2_event_dequeue(struct v4l2_fh *fh, struct v4l2_event *event,
		       int nonblocking)
{
	struct v4l2_events *events = fh->events;
	int ret;
	struct video_device_shadow *shvdev = video_device_shadow_get(fh->vdev);

	if (nonblocking)
		return __v4l2_event_dequeue(fh, event);

	/* Release the vdev lock while waiting */
	if (shvdev && shvdev->lock)
		mutex_unlock(shvdev->lock);

	do {
		ret = wait_event_interruptible(events->wait,
					       events->navailable != 0);
		if (ret < 0)
			break;

		ret = __v4l2_event_dequeue(fh, event);
	} while (ret == -ENOENT);

	if (shvdev && shvdev->lock)
		mutex_lock(shvdev->lock);

	return ret;
}