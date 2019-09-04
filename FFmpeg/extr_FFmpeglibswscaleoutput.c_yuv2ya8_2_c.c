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
typedef  int int16_t ;
typedef  int /*<<< orphan*/  SwsContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int av_clip_uint8 (int) ; 

__attribute__((used)) static void
yuv2ya8_2_c(SwsContext *c, const int16_t *buf[2],
            const int16_t *ubuf[2], const int16_t *vbuf[2],
            const int16_t *abuf[2], uint8_t *dest, int dstW,
            int yalpha, int uvalpha, int y)
{
    int hasAlpha = abuf && abuf[0] && abuf[1];
    const int16_t *buf0  = buf[0],  *buf1  = buf[1],
                  *abuf0 = hasAlpha ? abuf[0] : NULL,
                  *abuf1 = hasAlpha ? abuf[1] : NULL;
    int  yalpha1 = 4096 - yalpha;
    int i;

    av_assert2(yalpha  <= 4096U);

    for (i = 0; i < dstW; i++) {
        int Y = (buf0[i] * yalpha1 + buf1[i] * yalpha) >> 19;
        int A;

        Y = av_clip_uint8(Y);

        if (hasAlpha) {
            A = (abuf0[i] * yalpha1 + abuf1[i] * yalpha) >> 19;
            A = av_clip_uint8(A);
        }

        dest[i * 2    ] = Y;
        dest[i * 2 + 1] = hasAlpha ? A : 255;
    }
}