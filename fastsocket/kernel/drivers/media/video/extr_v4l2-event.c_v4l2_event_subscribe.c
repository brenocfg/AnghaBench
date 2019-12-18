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
struct v4l2_subscribed_event {int /*<<< orphan*/  list; int /*<<< orphan*/  type; } ;
struct v4l2_fh {struct v4l2_events* events; int /*<<< orphan*/  vdev; } ;
struct v4l2_events {int /*<<< orphan*/  subscribed; } ;
struct v4l2_event_subscription {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct v4l2_subscribed_event*) ; 
 struct v4l2_subscribed_event* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * v4l2_event_subscribed (struct v4l2_fh*,int /*<<< orphan*/ ) ; 
 struct video_device_shadow* video_device_shadow_get (int /*<<< orphan*/ ) ; 

int v4l2_event_subscribe(struct v4l2_fh *fh,
			 struct v4l2_event_subscription *sub)
{
	struct v4l2_events *events = fh->events;
	struct v4l2_subscribed_event *sev;
	unsigned long flags;
	struct video_device_shadow *shvdev = video_device_shadow_get(fh->vdev);

	if (fh->events == NULL || !shvdev) {
		WARN_ON(1);
		return -ENOMEM;
	}

	sev = kmalloc(sizeof(*sev), GFP_KERNEL);
	if (!sev)
		return -ENOMEM;

	spin_lock_irqsave(&shvdev->fh_lock, flags);

	if (v4l2_event_subscribed(fh, sub->type) == NULL) {
		INIT_LIST_HEAD(&sev->list);
		sev->type = sub->type;

		list_add(&sev->list, &events->subscribed);
		sev = NULL;
	}

	spin_unlock_irqrestore(&shvdev->fh_lock, flags);

	kfree(sev);

	return 0;
}