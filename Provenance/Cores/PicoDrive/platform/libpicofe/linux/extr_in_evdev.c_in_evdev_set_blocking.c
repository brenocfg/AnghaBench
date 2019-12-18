#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct input_event {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ in_evdev_t ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 long O_NONBLOCK ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int /*<<< orphan*/ ,struct input_event*,int) ; 

__attribute__((used)) static int in_evdev_set_blocking(in_evdev_t *dev, int y)
{
	long flags;
	int ret;

	flags = (long)fcntl(dev->fd, F_GETFL);
	if ((int)flags == -1) {
		perror("in_evdev: F_GETFL fcntl failed");
		return -1;
	}

	if (flags & O_NONBLOCK) {
		/* flush the event queue */
		struct input_event ev;
		do {
			ret = read(dev->fd, &ev, sizeof(ev));
		}
		while (ret == sizeof(ev));
	}

	if (y)
		flags &= ~O_NONBLOCK;
	else
		flags |=  O_NONBLOCK;
	ret = fcntl(dev->fd, F_SETFL, flags);
	if (ret == -1) {
		perror("in_evdev: F_SETFL fcntl failed");
		return -1;
	}

	return 0;
}