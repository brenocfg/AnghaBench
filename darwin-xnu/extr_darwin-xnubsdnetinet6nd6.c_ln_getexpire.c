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
struct rtentry {scalar_t__ base_calendartime; scalar_t__ base_uptime; } ;
struct llinfo_nd6 {scalar_t__ ln_expire; struct rtentry* ln_rt; } ;

/* Variables and functions */
 scalar_t__ NET_CALCULATE_CLOCKSKEW (struct timeval,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 int /*<<< orphan*/  net_uptime () ; 

__attribute__((used)) static uint64_t
ln_getexpire(struct llinfo_nd6 *ln)
{
	struct timeval caltime;
	uint64_t expiry;

	if (ln->ln_expire != 0) {
		struct rtentry *rt = ln->ln_rt;

		VERIFY(rt != NULL);
		/* account for system time change */
		getmicrotime(&caltime);

		rt->base_calendartime +=
		    NET_CALCULATE_CLOCKSKEW(caltime,
		    rt->base_calendartime, net_uptime(), rt->base_uptime);

		expiry = rt->base_calendartime +
		    ln->ln_expire - rt->base_uptime;
	} else {
		expiry = 0;
	}
	return (expiry);
}