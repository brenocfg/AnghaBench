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
typedef  scalar_t__ u_int64_t ;

/* Variables and functions */
 scalar_t__ _net_uptime ; 
 int /*<<< orphan*/  net_update_uptime () ; 

u_int64_t
net_uptime(void)
{
	if (_net_uptime == 0)
		net_update_uptime();

	return (_net_uptime);
}