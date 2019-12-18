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
struct timespec {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_2__ {int (* set_wallclock ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__ x86_platform ; 

int update_persistent_clock(struct timespec now)
{
	unsigned long flags;
	int retval;

	spin_lock_irqsave(&rtc_lock, flags);
	retval = x86_platform.set_wallclock(now.tv_sec);
	spin_unlock_irqrestore(&rtc_lock, flags);

	return retval;
}