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
struct compat_timeval {unsigned long tv_usec; unsigned long tv_sec; } ;
typedef  int /*<<< orphan*/  cputime_t ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long cputime_to_jiffies (int /*<<< orphan*/  const) ; 

__attribute__((used)) static __inline__ void
cputime_to_compat_timeval(const cputime_t cputime, struct compat_timeval *value)
{
	unsigned long jiffies = cputime_to_jiffies(cputime);
	value->tv_usec = (jiffies % HZ) * (1000000L / HZ);
	value->tv_sec = jiffies / HZ;
}