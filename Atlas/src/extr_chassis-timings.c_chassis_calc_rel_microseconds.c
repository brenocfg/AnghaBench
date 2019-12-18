#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  double guint64 ;
struct TYPE_2__ {double microseconds_frequency; } ;

/* Variables and functions */
 double MICROS_IN_SEC ; 
 TYPE_1__* chassis_timestamps_global ; 
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_critical (char*) ; 

guint64 chassis_calc_rel_microseconds(guint64 start, guint64 stop) {
#ifdef WIN32
	guint64 frequency;
	g_assert(chassis_timestamps_global != NULL);
	frequency = chassis_timestamps_global->microseconds_frequency;
	if (0 == frequency) {
		g_critical("High resolution counter QueryPerformanceCounter not available on this system. All timer values will be meaningless.");
		return stop - start;
	}
	return (guint64) ((stop - start) * (1.0 / frequency) * MICROS_IN_SEC);
#else
	return stop - start;
#endif
}