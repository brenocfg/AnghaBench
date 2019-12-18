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
typedef  size_t ptrdiff_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uint8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc1_inv_trans_4x4_c(uint8_t *dest, ptrdiff_t stride, int16_t *block)
{
    int i;
    register int t1, t2, t3, t4;
    int16_t *src, *dst;

    src = block;
    dst = block;
    for (i = 0; i < 4; i++) {
        t1 = 17 * (src[0] + src[2]) + 4;
        t2 = 17 * (src[0] - src[2]) + 4;
        t3 = 22 * src[1] + 10 * src[3];
        t4 = 22 * src[3] - 10 * src[1];

        dst[0] = (t1 + t3) >> 3;
        dst[1] = (t2 - t4) >> 3;
        dst[2] = (t2 + t4) >> 3;
        dst[3] = (t1 - t3) >> 3;

        src += 8;
        dst += 8;
    }

    src = block;
    for (i = 0; i < 4; i++) {
        t1 = 17 * (src[0] + src[16]) + 64;
        t2 = 17 * (src[0] - src[16]) + 64;
        t3 = 22 * src[8] + 10 * src[24];
        t4 = 22 * src[24] - 10 * src[8];

        dest[0 * stride] = av_clip_uint8(dest[0 * stride] + ((t1 + t3) >> 7));
        dest[1 * stride] = av_clip_uint8(dest[1 * stride] + ((t2 - t4) >> 7));
        dest[2 * stride] = av_clip_uint8(dest[2 * stride] + ((t2 + t4) >> 7));
        dest[3 * stride] = av_clip_uint8(dest[3 * stride] + ((t1 - t3) >> 7));

        src++;
        dest++;
    }
}