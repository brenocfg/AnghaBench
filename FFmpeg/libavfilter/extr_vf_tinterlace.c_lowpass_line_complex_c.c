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
 int av_clip_uint8 (int) ; 

__attribute__((used)) static void lowpass_line_complex_c(uint8_t *dstp, ptrdiff_t width, const uint8_t *srcp,
                                   ptrdiff_t mref, ptrdiff_t pref, int clip_max)
{
    const uint8_t *srcp_above = srcp + mref;
    const uint8_t *srcp_below = srcp + pref;
    const uint8_t *srcp_above2 = srcp + mref * 2;
    const uint8_t *srcp_below2 = srcp + pref * 2;
    int i, src_x, src_ab;
    for (i = 0; i < width; i++) {
        // this calculation is an integer representation of
        // '0.75 * current + 0.25 * above + 0.25 * below - 0.125 * above2 - 0.125 * below2'
        // '4 +' is for rounding.
        src_x   = srcp[i] << 1;
        src_ab  = srcp_above[i] + srcp_below[i];
        dstp[i] = av_clip_uint8((4 + ((srcp[i] + src_x + src_ab) << 1)
                                - srcp_above2[i] - srcp_below2[i]) >> 3);
        // Prevent over-sharpening:
        // dst must not exceed src when the average of above and below
        // is less than src. And the other way around.
        if (src_ab > src_x) {
            if (dstp[i] < srcp[i])
                dstp[i] = srcp[i];
        } else if (dstp[i] > srcp[i])
            dstp[i] = srcp[i];
    }
}