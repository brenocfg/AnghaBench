#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sn9c102_device {scalar_t__ stream; int state; TYPE_1__* v4ldev; int /*<<< orphan*/  wait_stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ) ; 
 int DEV_DISCONNECTED ; 
 int DEV_MISCONFIGURED ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  SN9C102_URB_TIMEOUT ; 
 scalar_t__ STREAM_INTERRUPT ; 
 scalar_t__ STREAM_OFF ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sn9c102_stream_interrupt(struct sn9c102_device* cam)
{
	long timeout;

	cam->stream = STREAM_INTERRUPT;
	timeout = wait_event_timeout(cam->wait_stream,
				     (cam->stream == STREAM_OFF) ||
				     (cam->state & DEV_DISCONNECTED),
				     SN9C102_URB_TIMEOUT);
	if (cam->state & DEV_DISCONNECTED)
		return -ENODEV;
	else if (cam->stream != STREAM_OFF) {
		cam->state |= DEV_MISCONFIGURED;
		DBG(1, "URB timeout reached. The camera is misconfigured. "
		       "To use it, close and open /dev/video%d again.",
		    cam->v4ldev->num);
		return -EIO;
	}

	return 0;
}