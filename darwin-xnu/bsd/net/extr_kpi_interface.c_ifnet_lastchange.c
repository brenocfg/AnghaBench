#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_sec; } ;
typedef  TYPE_2__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {struct timeval ifi_lastchange; } ;
struct TYPE_5__ {TYPE_1__ if_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ boottime_sec () ; 

errno_t
ifnet_lastchange(ifnet_t interface, struct timeval *last_change)
{
	if (interface == NULL)
		return (EINVAL);

	*last_change = interface->if_data.ifi_lastchange;
	/* Crude conversion from uptime to calendar time */
	last_change->tv_sec += boottime_sec();

	return (0);
}