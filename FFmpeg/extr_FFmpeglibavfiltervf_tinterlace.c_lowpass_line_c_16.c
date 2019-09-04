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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int av_le2ne16 (int const) ; 

__attribute__((used)) static void lowpass_line_c_16(uint8_t *dst8, ptrdiff_t width, const uint8_t *src8,
                              ptrdiff_t mref, ptrdiff_t pref, int clip_max)
{
    uint16_t *dstp = (uint16_t *)dst8;
    const uint16_t *srcp = (const uint16_t *)src8;
    const uint16_t *srcp_above = srcp + mref / 2;
    const uint16_t *srcp_below = srcp + pref / 2;
    int i, src_x;
    for (i = 0; i < width; i++) {
        // this calculation is an integer representation of
        // '0.5 * current + 0.25 * above + 0.25 * below'
        // '1 +' is for rounding.
        src_x   = av_le2ne16(srcp[i]) << 1;
        dstp[i] = av_le2ne16((1 + src_x + av_le2ne16(srcp_above[i])
                             + av_le2ne16(srcp_below[i])) >> 2);
    }
}