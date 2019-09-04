#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int int16_t ;
struct TYPE_8__ {int flags; TYPE_1__* comp; } ;
struct TYPE_7__ {int yuv2rgb_y_coeff; int yuv2rgb_v2r_coeff; int yuv2rgb_v2g_coeff; int yuv2rgb_u2g_coeff; int yuv2rgb_u2b_coeff; int /*<<< orphan*/  dstFormat; scalar_t__ yuv2rgb_y_offset; } ;
struct TYPE_6__ {int depth; } ;
typedef  TYPE_2__ SwsContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_ALPHA ; 
 int /*<<< orphan*/  HAVE_BIGENDIAN ; 
 int av_bswap16 (int) ; 
 int av_clip_uintp2 (int,int) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isBE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
yuv2gbrp_full_X_c(SwsContext *c, const int16_t *lumFilter,
                  const int16_t **lumSrc, int lumFilterSize,
                  const int16_t *chrFilter, const int16_t **chrUSrc,
                  const int16_t **chrVSrc, int chrFilterSize,
                  const int16_t **alpSrc, uint8_t **dest,
                  int dstW, int y)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(c->dstFormat);
    int i;
    int hasAlpha = (desc->flags & AV_PIX_FMT_FLAG_ALPHA) && alpSrc;
    uint16_t **dest16 = (uint16_t**)dest;
    int SH = 22 + 8 - desc->comp[0].depth;
    int A = 0; // init to silence warning

    for (i = 0; i < dstW; i++) {
        int j;
        int Y = 1 << 9;
        int U = (1 << 9) - (128 << 19);
        int V = (1 << 9) - (128 << 19);
        int R, G, B;

        for (j = 0; j < lumFilterSize; j++)
            Y += lumSrc[j][i] * lumFilter[j];

        for (j = 0; j < chrFilterSize; j++) {
            U += chrUSrc[j][i] * chrFilter[j];
            V += chrVSrc[j][i] * chrFilter[j];
        }

        Y >>= 10;
        U >>= 10;
        V >>= 10;

        if (hasAlpha) {
            A = 1 << 18;

            for (j = 0; j < lumFilterSize; j++)
                A += alpSrc[j][i] * lumFilter[j];

            if (A & 0xF8000000)
                A =  av_clip_uintp2(A, 27);
        }

        Y -= c->yuv2rgb_y_offset;
        Y *= c->yuv2rgb_y_coeff;
        Y += 1 << (SH-1);
        R = Y + V * c->yuv2rgb_v2r_coeff;
        G = Y + V * c->yuv2rgb_v2g_coeff + U * c->yuv2rgb_u2g_coeff;
        B = Y +                            U * c->yuv2rgb_u2b_coeff;

        if ((R | G | B) & 0xC0000000) {
            R = av_clip_uintp2(R, 30);
            G = av_clip_uintp2(G, 30);
            B = av_clip_uintp2(B, 30);
        }

        if (SH != 22) {
            dest16[0][i] = G >> SH;
            dest16[1][i] = B >> SH;
            dest16[2][i] = R >> SH;
            if (hasAlpha)
                dest16[3][i] = A >> (SH - 3);
        } else {
            dest[0][i] = G >> 22;
            dest[1][i] = B >> 22;
            dest[2][i] = R >> 22;
            if (hasAlpha)
                dest[3][i] = A >> 19;
        }
    }
    if (SH != 22 && (!isBE(c->dstFormat)) != (!HAVE_BIGENDIAN)) {
        for (i = 0; i < dstW; i++) {
            dest16[0][i] = av_bswap16(dest16[0][i]);
            dest16[1][i] = av_bswap16(dest16[1][i]);
            dest16[2][i] = av_bswap16(dest16[2][i]);
            if (hasAlpha)
                dest16[3][i] = av_bswap16(dest16[3][i]);
        }
    }
}