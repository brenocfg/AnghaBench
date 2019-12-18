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
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int av_le2ne16 (int const) ; 

__attribute__((used)) static void lowpass_line_complex_c_16(uint8_t *dst8, ptrdiff_t width, const uint8_t *src8,
                                      ptrdiff_t mref, ptrdiff_t pref, int clip_max)
{
    uint16_t *dstp = (uint16_t *)dst8;
    const uint16_t *srcp = (const uint16_t *)src8;
    const uint16_t *srcp_above = srcp + mref / 2;
    const uint16_t *srcp_below = srcp + pref / 2;
    const uint16_t *srcp_above2 = srcp + mref;
    const uint16_t *srcp_below2 = srcp + pref;
    int i, dst_le, src_le, src_x, src_ab;
    for (i = 0; i < width; i++) {
        // this calculation is an integer representation of
        // '0.75 * current + 0.25 * above + 0.25 * below - 0.125 * above2 - 0.125 * below2'
        // '4 +' is for rounding.
        src_le = av_le2ne16(srcp[i]);
        src_x  = src_le << 1;
        src_ab = av_le2ne16(srcp_above[i]) + av_le2ne16(srcp_below[i]);
        dst_le = av_clip((4 + ((src_le + src_x + src_ab) << 1)
                         - av_le2ne16(srcp_above2[i])
                         - av_le2ne16(srcp_below2[i])) >> 3, 0, clip_max);
        // Prevent over-sharpening:
        // dst must not exceed src when the average of above and below
        // is less than src. And the other way around.
        if (src_ab > src_x) {
            if (dst_le < src_le)
                dstp[i] = av_le2ne16(src_le);
            else
                dstp[i] = av_le2ne16(dst_le);
        } else if (dst_le > src_le) {
            dstp[i] = av_le2ne16(src_le);
        } else
            dstp[i] = av_le2ne16(dst_le);
    }
}