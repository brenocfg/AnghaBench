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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  net_perf_t ;

/* Variables and functions */
 int /*<<< orphan*/  microtime (struct timeval*) ; 

void net_perf_start_time(net_perf_t *npp, struct timeval *tv)
{
#pragma unused(npp)
	microtime(tv);
}