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
 scalar_t__ gp2x_get_ticks_us_ () ; 

__attribute__((used)) static unsigned int gp2x_get_ticks_ms_(void)
{
	/* approximate /= 1000 */
	unsigned long long v64;
	v64 = (unsigned long long)gp2x_get_ticks_us_() * 4294968;
	return v64 >> 32;
}