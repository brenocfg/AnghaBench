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
struct timeval {scalar_t__ tv_usec; } ;

/* Variables and functions */

__attribute__((used)) static unsigned time_diff(struct timeval *now, struct timeval *then)
{
	return (now->tv_usec >= then->tv_usec) ?
		now->tv_usec - then->tv_usec :
		1000000 - (then->tv_usec - now->tv_usec);
}