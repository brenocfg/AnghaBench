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
struct timespec {int dummy; } ;

/* Variables and functions */
 unsigned long long __lwp_wd_calc_ticks (struct timespec const*) ; 

unsigned long long timespec_to_ticks(const struct timespec *tp)
{
	return __lwp_wd_calc_ticks(tp);
}