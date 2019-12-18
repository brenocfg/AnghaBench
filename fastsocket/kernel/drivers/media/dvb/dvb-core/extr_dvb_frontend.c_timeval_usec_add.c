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
typedef  scalar_t__ u32 ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static inline void timeval_usec_add(struct timeval *curtime, u32 add_usec)
{
	curtime->tv_usec += add_usec;
	if (curtime->tv_usec >= 1000000) {
		curtime->tv_usec -= 1000000;
		curtime->tv_sec++;
	}
}