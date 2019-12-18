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
struct timespec {unsigned long tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  xen_read_wallclock (struct timespec*) ; 

unsigned long xen_get_wallclock(void)
{
	struct timespec ts;

	xen_read_wallclock(&ts);
	return ts.tv_sec;
}