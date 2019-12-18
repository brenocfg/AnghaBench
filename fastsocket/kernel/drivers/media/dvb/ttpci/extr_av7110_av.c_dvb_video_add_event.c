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
struct video_event {int dummy; } ;
struct dvb_video_events {int eventw; int eventr; int overflow; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  lock; int /*<<< orphan*/ * events; } ;
struct av7110 {struct dvb_video_events video_events; } ;

/* Variables and functions */
 int MAX_VIDEO_EVENT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct video_event*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void dvb_video_add_event(struct av7110 *av7110, struct video_event *event)
{
	struct dvb_video_events *events = &av7110->video_events;
	int wp;

	spin_lock_bh(&events->lock);

	wp = (events->eventw + 1) % MAX_VIDEO_EVENT;
	if (wp == events->eventr) {
		events->overflow = 1;
		events->eventr = (events->eventr + 1) % MAX_VIDEO_EVENT;
	}

	//FIXME: timestamp?
	memcpy(&events->events[events->eventw], event, sizeof(struct video_event));
	events->eventw = wp;

	spin_unlock_bh(&events->lock);

	wake_up_interruptible(&events->wait_queue);
}