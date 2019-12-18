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
typedef  int /*<<< orphan*/  u32 ;
struct timeval {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  timeval_usec_add (struct timeval*,int /*<<< orphan*/ ) ; 
 int timeval_usec_diff (struct timeval,struct timeval) ; 
 int /*<<< orphan*/  udelay (int) ; 

void dvb_frontend_sleep_until(struct timeval *waketime, u32 add_usec)
{
	struct timeval lasttime;
	s32 delta, newdelta;

	timeval_usec_add(waketime, add_usec);

	do_gettimeofday(&lasttime);
	delta = timeval_usec_diff(lasttime, *waketime);
	if (delta > 2500) {
		msleep((delta - 1500) / 1000);
		do_gettimeofday(&lasttime);
		newdelta = timeval_usec_diff(lasttime, *waketime);
		delta = (newdelta > delta) ? 0 : newdelta;
	}
	if (delta > 0)
		udelay(delta);
}