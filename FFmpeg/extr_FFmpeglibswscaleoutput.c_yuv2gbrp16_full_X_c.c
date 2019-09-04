#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  unsigned int int32_t ;
typedef  unsigned int int16_t ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {int yuv2rgb_y_coeff; int yuv2rgb_v2r_coeff; int yuv2rgb_v2g_coeff; int yuv2rgb_u2g_coeff; int yuv2rgb_u2b_coeff; int /*<<< orphan*/  dstFormat; scalar_t__ yuv2rgb_y_offset; } ;
typedef  TYPE_1__ SwsContext ;
typedef  TYPE_2__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_ALPHA ; 
 int /*<<< orphan*/  HAVE_BIGENDIAN ; 
 int av_bswap16 (int) ; 
 int av_clip_uintp2 (int,int) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isBE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
yuv2gbrp16_full_X_c(SwsContext *c, const int16_t *lumFilter,
                    const int16_t **lumSrcx, int lumFilterSize,
                    const int16_t *chrFilter, const int16_t **chrUSrcx,
                    const int16_t **chrVSrcx, int chrFilterSize,
                    const int16_t **alpSrcx, uint8_t **dest,
                    int dstW, int y)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(c->dstFormat);
    int i;
    int hasAlpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA) && alpSrcx;
    uint16_t **dest16 = (uint16_t**)dest;
    const int32_t **lumSrc  = (const int32_t**)lumSrcx;
    const int32_t **chrUSrc = (const int32_t**)chrUSrcx;
    const int32_t **chrVSrc = (const int32_t**)chrVSrcx;
    const int32_t **alpSrc  = (const int32_t**)alpSrcx;

    for (i = 0; i < dstW; i++) {
        int j;
        int Y = -0x40000000;
        int U = -(128 << 23);
        int V = -(128 << 23);
        int R, G, B, A;

        for (j = 0; j < lumFilterSize; j++)
            Y += lumSrc[j][i] * (unsigned)lumFilter[j];

        for (j = 0; j < chrFilterSize; j++) {
            U += chrUSrc[j][i] * (unsigned)chrFilter[j];
            V += chrVSrc[j][i] * (unsigned)chrFilter[j];
        }

        Y >>= 14;
        Y += 0x10000;
        U >>= 14;
        V >>= 14;

        if (hasAlpha) {
            A = -0x40000000;

            for (j = 0; j < lumFilterSize; j++)
                A += alpSrc[j][i] * lumFilter[j];

            A >>= 1;
            A += 0x20002000;
        }

        Y -= c->yuv2rgb_y_offset;
        Y *= c->yuv2rgb_y_coeff;
        Y += 1 << 13;
        R = V * c->yuv2rgb_v2r_coeff;
        G = V * c->yuv2rgb_v2g_coeff + U * c->yuv2rgb_u2g_coeff;
        B =                            U * c->yuv2rgb_u2b_coeff;

        R = av_clip_uintp2(Y + R, 30);
        G = av_clip_uintp2(Y + G, 30);
        B = av_clip_uintp2(Y + B, 30);

        dest16[0][i] = G >> 14;
        dest16[1][i] = B >> 14;
        dest16[2][i] = R >> 14;
        if (hasAlpha)
            dest16[3][i] = av_clip_uintp2(A, 30) >> 14;
    }
    if ((!isBE(c->dstFormat)) != (!HAVE_BIGENDIAN)) {
        for (i = 0; i < dstW; i++) {
            dest16[0][i] = av_bswap16(dest16[0][i]);
            dest16[1][i] = av_bswap16(dest16[1][i]);
            dest16[2][i] = av_bswap16(dest16[2][i]);
            if (hasAlpha)
                dest16[3][i] = av_bswap16(dest16[3][i]);
        }
    }
}