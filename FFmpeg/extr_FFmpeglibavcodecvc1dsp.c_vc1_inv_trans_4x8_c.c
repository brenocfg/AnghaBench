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

__attribute__((used)) static void vc1_inv_trans_4x8_c(uint8_t *dest, ptrdiff_t stride, int16_t *block)
{
    int i;
    register int t1, t2, t3, t4, t5, t6, t7, t8;
    int16_t *src, *dst;

    src = block;
    dst = block;

    for (i = 0; i < 8; i++) {
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
        t1 = 12 * (src[ 0] + src[32]) + 64;
        t2 = 12 * (src[ 0] - src[32]) + 64;
        t3 = 16 * src[16] +  6 * src[48];
        t4 =  6 * src[16] - 16 * src[48];

        t5 = t1 + t3;
        t6 = t2 + t4;
        t7 = t2 - t4;
        t8 = t1 - t3;

        t1 = 16 * src[ 8] + 15 * src[24] +  9 * src[40] +  4 * src[56];
        t2 = 15 * src[ 8] -  4 * src[24] - 16 * src[40] -  9 * src[56];
        t3 =  9 * src[ 8] - 16 * src[24] +  4 * src[40] + 15 * src[56];
        t4 =  4 * src[ 8] -  9 * src[24] + 15 * src[40] - 16 * src[56];

        dest[0 * stride] = av_clip_uint8(dest[0 * stride] + ((t5 + t1)     >> 7));
        dest[1 * stride] = av_clip_uint8(dest[1 * stride] + ((t6 + t2)     >> 7));
        dest[2 * stride] = av_clip_uint8(dest[2 * stride] + ((t7 + t3)     >> 7));
        dest[3 * stride] = av_clip_uint8(dest[3 * stride] + ((t8 + t4)     >> 7));
        dest[4 * stride] = av_clip_uint8(dest[4 * stride] + ((t8 - t4 + 1) >> 7));
        dest[5 * stride] = av_clip_uint8(dest[5 * stride] + ((t7 - t3 + 1) >> 7));
        dest[6 * stride] = av_clip_uint8(dest[6 * stride] + ((t6 - t2 + 1) >> 7));
        dest[7 * stride] = av_clip_uint8(dest[7 * stride] + ((t5 - t1 + 1) >> 7));

        src++;
        dest++;
    }
}