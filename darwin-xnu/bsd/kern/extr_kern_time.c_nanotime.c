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
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;

/* Variables and functions */
 int /*<<< orphan*/  clock_get_calendar_nanotime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
nanotime(
	struct timespec *tsp)
{
	clock_sec_t		tv_sec;
	clock_nsec_t	tv_nsec;

	clock_get_calendar_nanotime(&tv_sec, &tv_nsec);

	tsp->tv_sec = tv_sec;
	tsp->tv_nsec = tv_nsec;
}