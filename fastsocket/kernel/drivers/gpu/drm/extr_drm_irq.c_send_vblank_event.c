#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {unsigned long sequence; int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  pid; TYPE_1__* file_priv; int /*<<< orphan*/  link; } ;
struct drm_pending_vblank_event {TYPE_3__ event; int /*<<< orphan*/  pipe; TYPE_2__ base; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_wait; int /*<<< orphan*/  event_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_SMP (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_drm_vblank_event_delivered (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_vblank_event(struct drm_device *dev,
		struct drm_pending_vblank_event *e,
		unsigned long seq, struct timeval *now)
{
	WARN_ON_SMP(!spin_is_locked(&dev->event_lock));
	e->event.sequence = seq;
	e->event.tv_sec = now->tv_sec;
	e->event.tv_usec = now->tv_usec;

	list_add_tail(&e->base.link,
		      &e->base.file_priv->event_list);
	wake_up_interruptible(&e->base.file_priv->event_wait);
	trace_drm_vblank_event_delivered(e->base.pid, e->pipe,
					 e->event.sequence);
}