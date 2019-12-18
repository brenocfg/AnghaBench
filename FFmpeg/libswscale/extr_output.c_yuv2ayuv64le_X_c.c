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
typedef  unsigned int int32_t ;
typedef  scalar_t__ int16_t ;
typedef  int /*<<< orphan*/  SwsContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WL16 (int /*<<< orphan*/ *,int) ; 
 int av_clip_int16 (int) ; 

__attribute__((used)) static void
yuv2ayuv64le_X_c(SwsContext *c, const int16_t *lumFilter,
                 const int16_t **_lumSrc, int lumFilterSize,
                 const int16_t *chrFilter, const int16_t **_chrUSrc,
                 const int16_t **_chrVSrc, int chrFilterSize,
                 const int16_t **_alpSrc, uint8_t *dest, int dstW, int y)
{
    const int32_t **lumSrc  = (const int32_t **) _lumSrc,
                  **chrUSrc = (const int32_t **) _chrUSrc,
                  **chrVSrc = (const int32_t **) _chrVSrc,
                  **alpSrc  = (const int32_t **) _alpSrc;
    int hasAlpha = !!alpSrc;
    int i;

    for (i = 0; i < dstW; i++) {
        int Y = 1 << 14, U = 1 << 14;
        int V = 1 << 14, A = 1 << 14;
        int j;

        Y -= 0x40000000;
        U -= 0x40000000;
        V -= 0x40000000;
        A -= 0x40000000;

        for (j = 0; j < lumFilterSize; j++)
            Y += lumSrc[j][i] * (unsigned)lumFilter[j];

        for (j = 0; j < chrFilterSize; j++)
            U += chrUSrc[j][i] * (unsigned)chrFilter[j];

        for (j = 0; j < chrFilterSize; j++)
            V += chrVSrc[j][i] * (unsigned)chrFilter[j];

        if (hasAlpha)
            for (j = 0; j < lumFilterSize; j++)
                A += alpSrc[j][i] * (unsigned)lumFilter[j];

        Y = 0x8000 + av_clip_int16(Y >> 15);
        U = 0x8000 + av_clip_int16(U >> 15);
        V = 0x8000 + av_clip_int16(V >> 15);
        A = 0x8000 + av_clip_int16(A >> 15);

        AV_WL16(dest + 8 * i, hasAlpha ? A : 65535);
        AV_WL16(dest + 8 * i + 2, Y);
        AV_WL16(dest + 8 * i + 4, U);
        AV_WL16(dest + 8 * i + 6, V);
    }
}