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
struct uvc_buffer {scalar_t__ state; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ UVC_BUF_STATE_ACTIVE ; 
 scalar_t__ UVC_BUF_STATE_QUEUED ; 
 scalar_t__ UVC_BUF_STATE_READY ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uvc_queue_waiton(struct uvc_buffer *buf, int nonblocking)
{
	if (nonblocking) {
		return (buf->state != UVC_BUF_STATE_QUEUED &&
			buf->state != UVC_BUF_STATE_ACTIVE &&
			buf->state != UVC_BUF_STATE_READY)
			? 0 : -EAGAIN;
	}

	return wait_event_interruptible(buf->wait,
		buf->state != UVC_BUF_STATE_QUEUED &&
		buf->state != UVC_BUF_STATE_ACTIVE &&
		buf->state != UVC_BUF_STATE_READY);
}