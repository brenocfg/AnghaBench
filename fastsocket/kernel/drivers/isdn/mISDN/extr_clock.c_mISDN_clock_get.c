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
typedef  int /*<<< orphan*/  u_long ;
typedef  unsigned short u16 ;
typedef  int time_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_2__ {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 unsigned short iclock_count ; 
 int /*<<< orphan*/  iclock_lock ; 
 TYPE_1__ iclock_tv ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

unsigned short
mISDN_clock_get(void)
{
	u_long		flags;
	struct timeval	tv_now;
	time_t		elapsed_sec;
	int		elapsed_8000th;
	u16		count;

	read_lock_irqsave(&iclock_lock, flags);
	/* calc elapsed time by system clock */
	do_gettimeofday(&tv_now);
	elapsed_sec = tv_now.tv_sec - iclock_tv.tv_sec;
	elapsed_8000th = (tv_now.tv_usec / 125) - (iclock_tv.tv_usec / 125);
	if (elapsed_8000th < 0) {
		elapsed_sec -= 1;
		elapsed_8000th += 8000;
	}
	/* add elapsed time to counter */
	count =	iclock_count + elapsed_sec * 8000 + elapsed_8000th;
	read_unlock_irqrestore(&iclock_lock, flags);
	return count;
}