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
struct dvb_video_events {size_t eventw; size_t eventr; int /*<<< orphan*/  lock; int /*<<< orphan*/ * events; int /*<<< orphan*/  wait_queue; scalar_t__ overflow; } ;
struct av7110 {struct dvb_video_events video_events; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int EWOULDBLOCK ; 
 int MAX_VIDEO_EVENT ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  memcpy (struct video_event*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dvb_video_get_event (struct av7110 *av7110, struct video_event *event, int flags)
{
	struct dvb_video_events *events = &av7110->video_events;

	if (events->overflow) {
		events->overflow = 0;
		return -EOVERFLOW;
	}
	if (events->eventw == events->eventr) {
		int ret;

		if (flags & O_NONBLOCK)
			return -EWOULDBLOCK;

		ret = wait_event_interruptible(events->wait_queue,
					       events->eventw != events->eventr);
		if (ret < 0)
			return ret;
	}

	spin_lock_bh(&events->lock);

	memcpy(event, &events->events[events->eventr],
	       sizeof(struct video_event));
	events->eventr = (events->eventr + 1) % MAX_VIDEO_EVENT;

	spin_unlock_bh(&events->lock);

	return 0;
}