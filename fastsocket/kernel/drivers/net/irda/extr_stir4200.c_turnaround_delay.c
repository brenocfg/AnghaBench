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
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_2__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct stir_cb {TYPE_1__ rx_time; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ USEC_PER_SEC ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  udelay (long) ; 

__attribute__((used)) static void turnaround_delay(const struct stir_cb *stir, long us)
{
	long ticks;
	struct timeval now;

	if (us <= 0)
		return;

	do_gettimeofday(&now);
	if (now.tv_sec - stir->rx_time.tv_sec > 0)
		us -= USEC_PER_SEC;
	us -= now.tv_usec - stir->rx_time.tv_usec;
	if (us < 10)
		return;

	ticks = us / (1000000 / HZ);
	if (ticks > 0)
		schedule_timeout_interruptible(1 + ticks);
	else
		udelay(us);
}