#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int srcFormat; int srcW; } ;
typedef  TYPE_1__ SwsContext ;

/* Variables and functions */
#define  AV_PIX_FMT_BAYER_BGGR16BE 139 
#define  AV_PIX_FMT_BAYER_BGGR16LE 138 
#define  AV_PIX_FMT_BAYER_BGGR8 137 
#define  AV_PIX_FMT_BAYER_GBRG16BE 136 
#define  AV_PIX_FMT_BAYER_GBRG16LE 135 
#define  AV_PIX_FMT_BAYER_GBRG8 134 
#define  AV_PIX_FMT_BAYER_GRBG16BE 133 
#define  AV_PIX_FMT_BAYER_GRBG16LE 132 
#define  AV_PIX_FMT_BAYER_GRBG8 131 
#define  AV_PIX_FMT_BAYER_RGGB16BE 130 
#define  AV_PIX_FMT_BAYER_RGGB16LE 129 
#define  AV_PIX_FMT_BAYER_RGGB8 128 
 int /*<<< orphan*/  av_assert0 (int) ; 
 void bayer_bggr16be_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_bggr16be_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_bggr16le_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_bggr16le_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_bggr8_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_bggr8_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_gbrg16be_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_gbrg16be_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_gbrg16le_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_gbrg16le_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_gbrg8_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_gbrg8_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_grbg16be_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_grbg16be_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_grbg16le_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_grbg16le_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_grbg8_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_grbg8_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_rggb16be_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_rggb16be_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_rggb16le_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_rggb16le_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_rggb8_to_rgb24_copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 
 void bayer_rggb8_to_rgb24_interpolate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int bayer_to_rgb24_wrapper(SwsContext *c, const uint8_t* src[], int srcStride[], int srcSliceY,
                                  int srcSliceH, uint8_t* dst[], int dstStride[])
{
    uint8_t *dstPtr= dst[0] + srcSliceY * dstStride[0];
    const uint8_t *srcPtr= src[0];
    int i;
    void (*copy)       (const uint8_t *src, int src_stride, uint8_t *dst, int dst_stride, int width);
    void (*interpolate)(const uint8_t *src, int src_stride, uint8_t *dst, int dst_stride, int width);

    switch(c->srcFormat) {
#define CASE(pixfmt, prefix) \
    case pixfmt: copy        = bayer_##prefix##_to_rgb24_copy; \
                 interpolate = bayer_##prefix##_to_rgb24_interpolate; \
                 break;
    CASE(AV_PIX_FMT_BAYER_BGGR8,    bggr8)
    CASE(AV_PIX_FMT_BAYER_BGGR16LE, bggr16le)
    CASE(AV_PIX_FMT_BAYER_BGGR16BE, bggr16be)
    CASE(AV_PIX_FMT_BAYER_RGGB8,    rggb8)
    CASE(AV_PIX_FMT_BAYER_RGGB16LE, rggb16le)
    CASE(AV_PIX_FMT_BAYER_RGGB16BE, rggb16be)
    CASE(AV_PIX_FMT_BAYER_GBRG8,    gbrg8)
    CASE(AV_PIX_FMT_BAYER_GBRG16LE, gbrg16le)
    CASE(AV_PIX_FMT_BAYER_GBRG16BE, gbrg16be)
    CASE(AV_PIX_FMT_BAYER_GRBG8,    grbg8)
    CASE(AV_PIX_FMT_BAYER_GRBG16LE, grbg16le)
    CASE(AV_PIX_FMT_BAYER_GRBG16BE, grbg16be)
#undef CASE
    default: return 0;
    }

    av_assert0(srcSliceH > 1);

    copy(srcPtr, srcStride[0], dstPtr, dstStride[0], c->srcW);
    srcPtr += 2 * srcStride[0];
    dstPtr += 2 * dstStride[0];

    for (i = 2; i < srcSliceH - 2; i += 2) {
        interpolate(srcPtr, srcStride[0], dstPtr, dstStride[0], c->srcW);
        srcPtr += 2 * srcStride[0];
        dstPtr += 2 * dstStride[0];
    }

    if (i + 1 == srcSliceH) {
        copy(srcPtr, -srcStride[0], dstPtr, -dstStride[0], c->srcW);
    } else if (i < srcSliceH)
        copy(srcPtr, srcStride[0], dstPtr, dstStride[0], c->srcW);
    return srcSliceH;
}