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
struct timeval {int tv_sec; unsigned int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 

__attribute__((used)) static inline unsigned int mon_get_timestamp(void)
{
	struct timeval tval;
	unsigned int stamp;

	do_gettimeofday(&tval);
	stamp = tval.tv_sec & 0xFFFF;	/* 2^32 = 4294967296. Limit to 4096s. */
	stamp = stamp * 1000000 + tval.tv_usec;
	return stamp;
}