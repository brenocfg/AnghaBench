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
struct timebase_freq_t {int timebase_den; int /*<<< orphan*/  timebase_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  timebase_frequency_hz; } ;

/* Variables and functions */
 TYPE_1__ gPEClockFrequencyInfo ; 
 int /*<<< orphan*/  gTimebaseCallback (struct timebase_freq_t*) ; 

void
PE_call_timebase_callback(void)
{
	struct timebase_freq_t timebase_freq;

	timebase_freq.timebase_num = gPEClockFrequencyInfo.timebase_frequency_hz;
	timebase_freq.timebase_den = 1;

	if (gTimebaseCallback)
		gTimebaseCallback(&timebase_freq);
}