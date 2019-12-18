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
struct TYPE_2__ {int /*<<< orphan*/  sc_selp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_LOCK () ; 
 int /*<<< orphan*/  LOG_UNLOCK () ; 
 int os_log_wakeup ; 
 int /*<<< orphan*/  oslog_open ; 
 TYPE_1__ oslogsoftc ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 

void
oslogwakeup(void)
{
	LOG_LOCK();
	if (!oslog_open) {
		LOG_UNLOCK();
		return;
	}
	selwakeup(&oslogsoftc.sc_selp);
	os_log_wakeup = 1;
	LOG_UNLOCK();
}