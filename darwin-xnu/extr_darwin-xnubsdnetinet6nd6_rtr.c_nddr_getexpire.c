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
typedef  scalar_t__ uint64_t ;
struct timeval {int dummy; } ;
struct nd_defrouter {scalar_t__ expire; scalar_t__ base_calendartime; scalar_t__ base_uptime; } ;

/* Variables and functions */
 scalar_t__ NET_CALCULATE_CLOCKSKEW (struct timeval,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 int /*<<< orphan*/  net_uptime () ; 

uint64_t
nddr_getexpire(struct nd_defrouter *dr)
{
	struct timeval caltime;
	uint64_t expiry;

	if (dr->expire != 0) {
		/* account for system time change */
		getmicrotime(&caltime);

		dr->base_calendartime +=
		    NET_CALCULATE_CLOCKSKEW(caltime,
		    dr->base_calendartime, net_uptime(), dr->base_uptime);

		expiry = dr->base_calendartime +
		    dr->expire - dr->base_uptime;
	} else {
		expiry = 0;
	}
	return (expiry);
}