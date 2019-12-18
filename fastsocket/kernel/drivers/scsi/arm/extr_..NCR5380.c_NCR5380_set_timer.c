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
struct NCR5380_hostdata {int /*<<< orphan*/  coroutine; scalar_t__ time_expires; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void NCR5380_set_timer(struct NCR5380_hostdata *hostdata, unsigned long timeout)
{
	hostdata->time_expires = jiffies + timeout;
	schedule_delayed_work(&hostdata->coroutine, timeout);
}