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
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int do_sys_settimeofday (struct timespec const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int posix_clock_realtime_set(const clockid_t which_clock,
				    const struct timespec *tp)
{
	return do_sys_settimeofday(tp, NULL);
}