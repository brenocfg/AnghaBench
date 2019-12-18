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

__attribute__((used)) static void vc1_inv_trans_8x4_c(uint8_t *dest, ptrdiff_t stride, int16_t *block)
{
    int i;
    register int t1, t2, t3, t4, t5, t6, t7, t8;
    int16_t *src, *dst;

    src = block;
    dst = block;

    for (i = 0; i < 4; i++) {
        t1 = 12 * (src[0] + src[4]) + 4;
        t2 = 12 * (src[0] - src[4]) + 4;
        t3 = 16 * src[2] +  6 * src[6];
        t4 =  6 * src[2] - 16 * src[6];

        t5 = t1 + t3;
        t6 = t2 + t4;
        t7 = t2 - t4;
        t8 = t1 - t3;

        t1 = 16 * src[1] + 15 * src[3] +  9 * src[5] +  4 * src[7];
        t2 = 15 * src[1] -  4 * src[3] - 16 * src[5] -  9 * src[7];
        t3 =  9 * src[1] - 16 * src[3] +  4 * src[5] + 15 * src[7];
        t4 =  4 * src[1] -  9 * src[3] + 15 * src[5] - 16 * src[7];

        dst[0] = (t5 + t1) >> 3;
        dst[1] = (t6 + t2) >> 3;
        dst[2] = (t7 + t3) >> 3;
        dst[3] = (t8 + t4) >> 3;
        dst[4] = (t8 - t4) >> 3;
        dst[5] = (t7 - t3) >> 3;
        dst[6] = (t6 - t2) >> 3;
        dst[7] = (t5 - t1) >> 3;

        src += 8;
        dst += 8;
    }

    src = block;
    for (i = 0; i < 8; i++) {
        t1 = 17 * (src[ 0] + src[16]) + 64;
        t2 = 17 * (src[ 0] - src[16]) + 64;
        t3 = 22 * src[ 8] + 10 * src[24];
        t4 = 22 * src[24] - 10 * src[ 8];

        dest[0 * stride] = av_clip_uint8(dest[0 * stride] + ((t1 + t3) >> 7));
        dest[1 * stride] = av_clip_uint8(dest[1 * stride] + ((t2 - t4) >> 7));
        dest[2 * stride] = av_clip_uint8(dest[2 * stride] + ((t2 + t4) >> 7));
        dest[3 * stride] = av_clip_uint8(dest[3 * stride] + ((t1 - t3) >> 7));

        src++;
        dest++;
    }
}