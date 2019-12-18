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
typedef  int uint64_t ;
struct menu_device {int* intervals; int expected_us; int predicted_us; } ;

/* Variables and functions */
 int INTERVALS ; 
 int STDDEV_THRESH ; 

__attribute__((used)) static void detect_repeating_patterns(struct menu_device *data)
{
	int i;
	uint64_t avg = 0;
	uint64_t stddev = 0; /* contains the square of the std deviation */

	/* first calculate average and standard deviation of the past */
	for (i = 0; i < INTERVALS; i++)
		avg += data->intervals[i];
	avg = avg / INTERVALS;

	/* if the avg is beyond the known next tick, it's worthless */
	if (avg > data->expected_us)
		return;

	for (i = 0; i < INTERVALS; i++)
		stddev += (data->intervals[i] - avg) *
			  (data->intervals[i] - avg);

	stddev = stddev / INTERVALS;

	/*
	 * now.. if stddev is small.. then assume we have a
	 * repeating pattern and predict we keep doing this.
	 */

	if (avg && stddev < STDDEV_THRESH)
		data->predicted_us = avg;
}