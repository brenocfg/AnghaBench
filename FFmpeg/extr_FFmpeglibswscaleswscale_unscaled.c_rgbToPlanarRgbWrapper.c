#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int srcFormat; int dstFormat; int /*<<< orphan*/  srcW; } ;
typedef  TYPE_1__ SwsContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PIX_FMT_ABGR 133 
#define  AV_PIX_FMT_ARGB 132 
#define  AV_PIX_FMT_BGR24 131 
#define  AV_PIX_FMT_BGRA 130 
#define  AV_PIX_FMT_RGB24 129 
#define  AV_PIX_FMT_RGBA 128 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packedtogbr24p (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ **,int*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rgbToPlanarRgbWrapper(SwsContext *c, const uint8_t *src[],
                                 int srcStride[], int srcSliceY, int srcSliceH,
                                 uint8_t *dst[], int dstStride[])
{
    int alpha_first = 0;
    int stride102[] = { dstStride[1], dstStride[0], dstStride[2] };
    int stride201[] = { dstStride[2], dstStride[0], dstStride[1] };
    uint8_t *dst102[] = { dst[1] + srcSliceY * dstStride[1],
                          dst[0] + srcSliceY * dstStride[0],
                          dst[2] + srcSliceY * dstStride[2] };
    uint8_t *dst201[] = { dst[2] + srcSliceY * dstStride[2],
                          dst[0] + srcSliceY * dstStride[0],
                          dst[1] + srcSliceY * dstStride[1] };

    switch (c->srcFormat) {
    case AV_PIX_FMT_RGB24:
        packedtogbr24p((const uint8_t *) src[0], srcStride[0], dst201,
                       stride201, srcSliceH, alpha_first, 3, c->srcW);
        break;
    case AV_PIX_FMT_BGR24:
        packedtogbr24p((const uint8_t *) src[0], srcStride[0], dst102,
                       stride102, srcSliceH, alpha_first, 3, c->srcW);
        break;
    case AV_PIX_FMT_ARGB:
        alpha_first = 1;
    case AV_PIX_FMT_RGBA:
        packedtogbr24p((const uint8_t *) src[0], srcStride[0], dst201,
                       stride201, srcSliceH, alpha_first, 4, c->srcW);
        break;
    case AV_PIX_FMT_ABGR:
        alpha_first = 1;
    case AV_PIX_FMT_BGRA:
        packedtogbr24p((const uint8_t *) src[0], srcStride[0], dst102,
                       stride102, srcSliceH, alpha_first, 4, c->srcW);
        break;
    default:
        av_log(c, AV_LOG_ERROR,
               "unsupported planar RGB conversion %s -> %s\n",
               av_get_pix_fmt_name(c->srcFormat),
               av_get_pix_fmt_name(c->dstFormat));
    }

    return srcSliceH;
}