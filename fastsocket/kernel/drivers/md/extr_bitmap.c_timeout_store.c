#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long daemon_sleep; } ;
struct mddev {TYPE_2__* thread; TYPE_1__ bitmap_info; } ;
typedef  int ssize_t ;
struct TYPE_4__ {unsigned long timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long HZ ; 
 unsigned long LONG_MAX ; 
 unsigned long MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  md_wakeup_thread (TYPE_2__*) ; 
 int strict_strtoul_scaled (char const*,unsigned long*,int) ; 

__attribute__((used)) static ssize_t
timeout_store(struct mddev *mddev, const char *buf, size_t len)
{
	/* timeout can be set at any time */
	unsigned long timeout;
	int rv = strict_strtoul_scaled(buf, &timeout, 4);
	if (rv)
		return rv;

	/* just to make sure we don't overflow... */
	if (timeout >= LONG_MAX / HZ)
		return -EINVAL;

	timeout = timeout * HZ / 10000;

	if (timeout >= MAX_SCHEDULE_TIMEOUT)
		timeout = MAX_SCHEDULE_TIMEOUT-1;
	if (timeout < 1)
		timeout = 1;
	mddev->bitmap_info.daemon_sleep = timeout;
	if (mddev->thread) {
		/* if thread->timeout is MAX_SCHEDULE_TIMEOUT, then
		 * the bitmap is all clean and we don't need to
		 * adjust the timeout right now
		 */
		if (mddev->thread->timeout < MAX_SCHEDULE_TIMEOUT) {
			mddev->thread->timeout = timeout;
			md_wakeup_thread(mddev->thread);
		}
	}
	return len;
}