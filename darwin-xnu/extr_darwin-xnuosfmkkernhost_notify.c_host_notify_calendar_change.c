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
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {int /*<<< orphan*/  Head; } ;
typedef  TYPE_1__ __Request__host_calendar_changed_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_NOTIFY_CALENDAR_CHANGE ; 
 int /*<<< orphan*/  host_notify_all (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void
host_notify_calendar_change(void)
{
	__Request__host_calendar_changed_t	msg;

	host_notify_all(HOST_NOTIFY_CALENDAR_CHANGE, &msg.Head, sizeof (msg));
}