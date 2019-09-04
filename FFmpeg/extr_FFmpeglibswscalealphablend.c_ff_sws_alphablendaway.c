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
typedef  int ptrdiff_t ;
struct TYPE_8__ {int nb_components; int flags; int log2_chroma_w; int log2_chroma_h; TYPE_1__* comp; } ;
struct TYPE_7__ {scalar_t__ alphablend; int chrSrcW; int srcW; int /*<<< orphan*/  srcFormat; } ;
struct TYPE_6__ {int depth; int offset; } ;
typedef  TYPE_2__ SwsContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int) ; 
 int AV_PIX_FMT_FLAG_PLANAR ; 
 int AV_PIX_FMT_FLAG_RGB ; 
 int /*<<< orphan*/  HAVE_BIGENDIAN ; 
 scalar_t__ SWS_ALPHA_BLEND_CHECKERBOARD ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 unsigned int av_bswap16 (int const) ; 
 int av_clip (unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isBE (int /*<<< orphan*/ ) ; 
 scalar_t__ isGray (int /*<<< orphan*/ ) ; 

int ff_sws_alphablendaway(SwsContext *c, const uint8_t *src[],
                          int srcStride[], int srcSliceY, int srcSliceH,
                          uint8_t *dst[], int dstStride[])
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(c->srcFormat);
    int nb_components = desc->nb_components;
    int plane, x, y;
    int plane_count = isGray(c->srcFormat) ? 1 : 3;
    int sixteen_bits = desc->comp[0].depth >= 9;
    unsigned off    = 1<<(desc->comp[0].depth - 1);
    unsigned shift  = desc->comp[0].depth;
    unsigned max    = (1<<shift) - 1;
    int target_table[2][3];

    for (plane = 0; plane < plane_count; plane++) {
        int a = 0, b = 0;
        if (c->alphablend == SWS_ALPHA_BLEND_CHECKERBOARD) {
            a = (1<<(desc->comp[0].depth - 1))/2;
            b = 3*(1<<(desc->comp[0].depth-1))/2;
        }
        target_table[0][plane] = plane && !(desc->flags & AV_PIX_FMT_FLAG_RGB) ? 1<<(desc->comp[0].depth - 1) : a;
        target_table[1][plane] = plane && !(desc->flags & AV_PIX_FMT_FLAG_RGB) ? 1<<(desc->comp[0].depth - 1) : b;
    }

    av_assert0(plane_count == nb_components - 1);
    if (desc->flags & AV_PIX_FMT_FLAG_PLANAR) {
        for (plane = 0; plane < plane_count; plane++) {
            int w = plane ? c->chrSrcW : c->srcW;
            int x_subsample = plane ? desc->log2_chroma_w: 0;
            int y_subsample = plane ? desc->log2_chroma_h: 0;
            for (y = srcSliceY >> y_subsample; y < AV_CEIL_RSHIFT(srcSliceH, y_subsample); y++) {
                if (x_subsample || y_subsample) {
                    int alpha;
                    unsigned u;
                    if (sixteen_bits) {
                        ptrdiff_t alpha_step = srcStride[plane_count] >> 1;
                        const uint16_t *s = (const uint16_t *)(src[plane      ] +  srcStride[plane      ] * y);
                        const uint16_t *a = (const uint16_t *)(src[plane_count] + (srcStride[plane_count] * y << y_subsample));
                              uint16_t *d = (      uint16_t *)(dst[plane      ] +  dstStride[plane      ] * y);
                        if ((!isBE(c->srcFormat)) == !HAVE_BIGENDIAN) {
                            for (x = 0; x < w; x++) {
                                if (y_subsample) {
                                    alpha = (a[2*x]              + a[2*x + 1] + 2 +
                                             a[2*x + alpha_step] + a[2*x + alpha_step + 1]) >> 2;
                                } else
                                    alpha = (a[2*x] + a[2*x + 1]) >> 1;
                                u = s[x]*alpha + target_table[((x^y)>>5)&1][plane]*(max-alpha) + off;
                                d[x] = av_clip((u + (u >> shift)) >> shift, 0, max);
                            }
                        } else {
                            for (x = 0; x < w; x++) {
                                if (y_subsample) {
                                    alpha = (av_bswap16(a[2*x])              + av_bswap16(a[2*x + 1]) + 2 +
                                             av_bswap16(a[2*x + alpha_step]) + av_bswap16(a[2*x + alpha_step + 1])) >> 2;
                                } else
                                    alpha = (av_bswap16(a[2*x]) + av_bswap16(a[2*x + 1])) >> 1;
                                u = av_bswap16(s[x])*alpha + target_table[((x^y)>>5)&1][plane]*(max-alpha) + off;
                                d[x] = av_clip((u + (u >> shift)) >> shift, 0, max);
                            }
                        }
                    } else {
                        ptrdiff_t alpha_step = srcStride[plane_count];
                        const uint8_t *s = src[plane      ] + srcStride[plane] * y;
                        const uint8_t *a = src[plane_count] + (srcStride[plane_count] * y << y_subsample);
                              uint8_t *d = dst[plane      ] + dstStride[plane] * y;
                        for (x = 0; x < w; x++) {
                            if (y_subsample) {
                                alpha = (a[2*x]              + a[2*x + 1] + 2 +
                                         a[2*x + alpha_step] + a[2*x + alpha_step + 1]) >> 2;
                            } else
                                alpha = (a[2*x] + a[2*x + 1]) >> 1;
                            u = s[x]*alpha + target_table[((x^y)>>5)&1][plane]*(255-alpha) + 128;
                            d[x] = (257*u) >> 16;
                        }
                    }
                } else {
                if (sixteen_bits) {
                    const uint16_t *s = (const uint16_t *)(src[plane      ] + srcStride[plane      ] * y);
                    const uint16_t *a = (const uint16_t *)(src[plane_count] + srcStride[plane_count] * y);
                          uint16_t *d = (      uint16_t *)(dst[plane      ] + dstStride[plane      ] * y);
                    if ((!isBE(c->srcFormat)) == !HAVE_BIGENDIAN) {
                        for (x = 0; x < w; x++) {
                            unsigned u = s[x]*a[x] + target_table[((x^y)>>5)&1][plane]*(max-a[x]) + off;
                            d[x] = av_clip((u + (u >> shift)) >> shift, 0, max);
                        }
                    } else {
                        for (x = 0; x < w; x++) {
                            unsigned aswap =av_bswap16(a[x]);
                            unsigned u = av_bswap16(s[x])*aswap + target_table[((x^y)>>5)&1][plane]*(max-aswap) + off;
                            d[x] = av_clip((u + (u >> shift)) >> shift, 0, max);
                        }
                    }
                } else {
                    const uint8_t *s = src[plane      ] + srcStride[plane] * y;
                    const uint8_t *a = src[plane_count] + srcStride[plane_count] * y;
                          uint8_t *d = dst[plane      ] + dstStride[plane] * y;
                    for (x = 0; x < w; x++) {
                        unsigned u = s[x]*a[x] + target_table[((x^y)>>5)&1][plane]*(255-a[x]) + 128;
                        d[x] = (257*u) >> 16;
                    }
                }
                }
            }
        }
    } else {
        int alpha_pos = desc->comp[plane_count].offset;
        int w = c->srcW;
        for (y = srcSliceY; y < srcSliceH; y++) {
            if (sixteen_bits) {
                const uint16_t *s = (const uint16_t *)(src[0] + srcStride[0] * y + 2*!alpha_pos);
                const uint16_t *a = (const uint16_t *)(src[0] + srcStride[0] * y +    alpha_pos);
                      uint16_t *d = (      uint16_t *)(dst[0] + dstStride[0] * y);
                if ((!isBE(c->srcFormat)) == !HAVE_BIGENDIAN) {
                    for (x = 0; x < w; x++) {
                        for (plane = 0; plane < plane_count; plane++) {
                            int x_index = (plane_count + 1) * x;
                            unsigned u = s[x_index + plane]*a[x_index] + target_table[((x^y)>>5)&1][plane]*(max-a[x_index]) + off;
                            d[plane_count*x + plane] = av_clip((u + (u >> shift)) >> shift, 0, max);
                        }
                    }
                } else {
                    for (x = 0; x < w; x++) {
                        for (plane = 0; plane < plane_count; plane++) {
                            int x_index = (plane_count + 1) * x;
                            unsigned aswap =av_bswap16(a[x_index]);
                            unsigned u = av_bswap16(s[x_index + plane])*aswap + target_table[((x^y)>>5)&1][plane]*(max-aswap) + off;
                            d[plane_count*x + plane] = av_clip((u + (u >> shift)) >> shift, 0, max);
                        }
                    }
                }
            } else {
                const uint8_t *s = src[0] + srcStride[0] * y + !alpha_pos;
                const uint8_t *a = src[0] + srcStride[0] * y + alpha_pos;
                      uint8_t *d = dst[0] + dstStride[0] * y;
                for (x = 0; x < w; x++) {
                    for (plane = 0; plane < plane_count; plane++) {
                        int x_index = (plane_count + 1) * x;
                        unsigned u = s[x_index + plane]*a[x_index] + target_table[((x^y)>>5)&1][plane]*(255-a[x_index]) + 128;
                        d[plane_count*x + plane] = (257*u) >> 16;
                    }
                }
            }
        }
    }

    return 0;
}