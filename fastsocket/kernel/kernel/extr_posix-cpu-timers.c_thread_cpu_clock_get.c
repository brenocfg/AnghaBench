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
 int /*<<< orphan*/  THREAD_CLOCK ; 
 int posix_cpu_clock_get (int /*<<< orphan*/ ,struct timespec*) ; 

__attribute__((used)) static int thread_cpu_clock_get(const clockid_t which_clock,
				struct timespec *tp)
{
	return posix_cpu_clock_get(THREAD_CLOCK, tp);
}