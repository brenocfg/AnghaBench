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
struct v4l2_subscribed_event {int /*<<< orphan*/  list; } ;
struct v4l2_fh {int /*<<< orphan*/  vdev; } ;
struct v4l2_event_subscription {scalar_t__ type; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ V4L2_EVENT_ALL ; 
 int /*<<< orphan*/  kfree (struct v4l2_subscribed_event*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct v4l2_subscribed_event* v4l2_event_subscribed (struct v4l2_fh*,scalar_t__) ; 
 int /*<<< orphan*/  v4l2_event_unsubscribe_all (struct v4l2_fh*) ; 
 struct video_device_shadow* video_device_shadow_get (int /*<<< orphan*/ ) ; 

int v4l2_event_unsubscribe(struct v4l2_fh *fh,
			   struct v4l2_event_subscription *sub)
{
	struct v4l2_subscribed_event *sev;
	unsigned long flags;
	struct video_device_shadow *shvdev = video_device_shadow_get(fh->vdev);

	if (sub->type == V4L2_EVENT_ALL) {
		v4l2_event_unsubscribe_all(fh);
		return 0;
	}

	if (!shvdev)
		return -ENOMEM;

	spin_lock_irqsave(&shvdev->fh_lock, flags);

	sev = v4l2_event_subscribed(fh, sub->type);
	if (sev != NULL)
		list_del(&sev->list);

	spin_unlock_irqrestore(&shvdev->fh_lock, flags);

	kfree(sev);

	return 0;
}