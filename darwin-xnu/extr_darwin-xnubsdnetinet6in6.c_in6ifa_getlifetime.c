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
struct timeval {int dummy; } ;
struct in6_addrlifetime_i {scalar_t__ ia6ti_vltime; scalar_t__ ia6ti_pltime; scalar_t__ ia6ti_base_calendartime; scalar_t__ ia6ti_base_uptime; scalar_t__ ia6ti_expire; scalar_t__ ia6ti_preferred; } ;
struct in6_ifaddr {struct in6_addrlifetime_i ia6_lifetime; } ;
struct in6_addrlifetime {scalar_t__ ia6t_vltime; scalar_t__ ia6t_pltime; scalar_t__ ia6t_expire; scalar_t__ ia6t_preferred; } ;

/* Variables and functions */
 scalar_t__ ND6_INFINITE_LIFETIME ; 
 scalar_t__ NET_CALCULATE_CLOCKSKEW (struct timeval,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 int /*<<< orphan*/  net_uptime () ; 

void
in6ifa_getlifetime(struct in6_ifaddr *ia6, struct in6_addrlifetime *t_dst,
    int iscalendar)
{
	struct in6_addrlifetime_i *t_src = &ia6->ia6_lifetime;
	struct timeval caltime;

	t_dst->ia6t_vltime = t_src->ia6ti_vltime;
	t_dst->ia6t_pltime = t_src->ia6ti_pltime;
	t_dst->ia6t_expire = 0;
	t_dst->ia6t_preferred = 0;

	/* account for system time change */
	getmicrotime(&caltime);
	t_src->ia6ti_base_calendartime +=
	    NET_CALCULATE_CLOCKSKEW(caltime,
	    t_src->ia6ti_base_calendartime, net_uptime(),
	    t_src->ia6ti_base_uptime);

	if (iscalendar) {
		if (t_src->ia6ti_expire != 0 &&
		    t_src->ia6ti_vltime != ND6_INFINITE_LIFETIME)
			t_dst->ia6t_expire = t_src->ia6ti_base_calendartime +
			    t_src->ia6ti_expire - t_src->ia6ti_base_uptime;

		if (t_src->ia6ti_preferred != 0 &&
		    t_src->ia6ti_pltime != ND6_INFINITE_LIFETIME)
			t_dst->ia6t_preferred = t_src->ia6ti_base_calendartime +
			    t_src->ia6ti_preferred - t_src->ia6ti_base_uptime;
	} else {
		if (t_src->ia6ti_expire != 0 &&
		    t_src->ia6ti_vltime != ND6_INFINITE_LIFETIME)
			t_dst->ia6t_expire = t_src->ia6ti_expire;

		if (t_src->ia6ti_preferred != 0 &&
		    t_src->ia6ti_pltime != ND6_INFINITE_LIFETIME)
			t_dst->ia6t_preferred = t_src->ia6ti_preferred;
	}
}