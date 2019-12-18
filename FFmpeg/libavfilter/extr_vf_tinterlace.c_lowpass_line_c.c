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
typedef  int uint8_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static void lowpass_line_c(uint8_t *dstp, ptrdiff_t width, const uint8_t *srcp,
                           ptrdiff_t mref, ptrdiff_t pref, int clip_max)
{
    const uint8_t *srcp_above = srcp + mref;
    const uint8_t *srcp_below = srcp + pref;
    int i;
    for (i = 0; i < width; i++) {
        // this calculation is an integer representation of
        // '0.5 * current + 0.25 * above + 0.25 * below'
        // '1 +' is for rounding.
        dstp[i] = (1 + srcp[i] + srcp[i] + srcp_above[i] + srcp_below[i]) >> 2;
    }
}