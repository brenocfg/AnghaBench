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

/* Variables and functions */
 int threshold ; 

__attribute__((used)) static int atp_calculate_abs(int *xy_sensors, int nb_sensors, int fact,
			     int *z, int *fingers)
{
	int i;
	/* values to calculate mean */
	int pcum = 0, psum = 0;
	int is_increasing = 0;

	*fingers = 0;

	for (i = 0; i < nb_sensors; i++) {
		if (xy_sensors[i] < threshold) {
			if (is_increasing)
				is_increasing = 0;

			continue;
		}

		/*
		 * Makes the finger detection more versatile.  For example,
		 * two fingers with no gap will be detected.  Also, my
		 * tests show it less likely to have intermittent loss
		 * of multiple finger readings while moving around (scrolling).
		 *
		 * Changes the multiple finger detection to counting humps on
		 * sensors (transitions from nonincreasing to increasing)
		 * instead of counting transitions from low sensors (no
		 * finger reading) to high sensors (finger above
		 * sensor)
		 *
		 * - Jason Parekh <jasonparekh@gmail.com>
		 */
		if (i < 1 ||
		    (!is_increasing && xy_sensors[i - 1] < xy_sensors[i])) {
			(*fingers)++;
			is_increasing = 1;
		} else if (i > 0 && (xy_sensors[i - 1] - xy_sensors[i] > threshold)) {
			is_increasing = 0;
		}

		/*
		 * Subtracts threshold so a high sensor that just passes the
		 * threshold won't skew the calculated absolute coordinate.
		 * Fixes an issue where slowly moving the mouse would
		 * occasionally jump a number of pixels (slowly moving the
		 * finger makes this issue most apparent.)
		 */
		pcum += (xy_sensors[i] - threshold) * i;
		psum += (xy_sensors[i] - threshold);
	}

	if (psum > 0) {
		*z = psum;
		return pcum * fact / psum;
	}

	return 0;
}