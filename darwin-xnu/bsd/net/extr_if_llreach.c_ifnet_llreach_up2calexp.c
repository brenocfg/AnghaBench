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
struct timeval {scalar_t__ tv_sec; } ;
struct if_llreach {scalar_t__ lr_basecal; scalar_t__ lr_baseup; scalar_t__ lr_reachable; } ;

/* Variables and functions */
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 scalar_t__ net_uptime () ; 

u_int64_t
ifnet_llreach_up2calexp(struct if_llreach *lr, u_int64_t uptime)
{
	u_int64_t calendar = 0;

	if (uptime != 0) {
		struct timeval cnow;
		u_int64_t unow;

		getmicrotime(&cnow);	/* current calendar time */
		unow = net_uptime();	/* current approx. uptime */
		/*
		 * Take into account possible calendar time changes;
		 * adjust base calendar value if necessary, i.e.
		 * the calendar skew should equate to the uptime skew.
		 */
		lr->lr_basecal += (cnow.tv_sec - lr->lr_basecal) -
		    (unow - lr->lr_baseup);

		calendar = lr->lr_basecal + lr->lr_reachable +
		    (uptime - lr->lr_baseup);
	}

	return (calendar);
}