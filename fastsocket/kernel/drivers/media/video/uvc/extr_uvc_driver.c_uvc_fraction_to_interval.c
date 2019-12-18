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
typedef  int uint32_t ;

/* Variables and functions */

uint32_t uvc_fraction_to_interval(uint32_t numerator, uint32_t denominator)
{
	uint32_t multiplier;

	/* Saturate the result if the operation would overflow. */
	if (denominator == 0 ||
	    numerator/denominator >= ((uint32_t)-1)/10000000)
		return (uint32_t)-1;

	/* Divide both the denominator and the multiplier by two until
	 * numerator * multiplier doesn't overflow. If anyone knows a better
	 * algorithm please let me know.
	 */
	multiplier = 10000000;
	while (numerator > ((uint32_t)-1)/multiplier) {
		multiplier /= 2;
		denominator /= 2;
	}

	return denominator ? numerator * multiplier / denominator : 0;
}