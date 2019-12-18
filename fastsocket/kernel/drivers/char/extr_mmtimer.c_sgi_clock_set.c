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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
typedef  int /*<<< orphan*/  clockid_t ;
struct TYPE_2__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 scalar_t__ div_u64_rem (int,scalar_t__,scalar_t__*) ; 
 int rtc_time () ; 
 TYPE_1__ sgi_clock_offset ; 
 int sgi_clock_period ; 

__attribute__((used)) static int sgi_clock_set(const clockid_t clockid, const struct timespec *tp)
{

	u64 nsec;
	u32 rem;

	nsec = rtc_time() * sgi_clock_period;

	sgi_clock_offset.tv_sec = tp->tv_sec - div_u64_rem(nsec, NSEC_PER_SEC, &rem);

	if (rem <= tp->tv_nsec)
		sgi_clock_offset.tv_nsec = tp->tv_sec - rem;
	else {
		sgi_clock_offset.tv_nsec = tp->tv_sec + NSEC_PER_SEC - rem;
		sgi_clock_offset.tv_sec--;
	}
	return 0;
}