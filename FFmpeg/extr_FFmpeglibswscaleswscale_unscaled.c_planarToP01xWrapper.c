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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {TYPE_1__* comp; } ;
struct TYPE_7__ {int srcW; int /*<<< orphan*/  dstFormat; int /*<<< orphan*/  srcFormat; } ;
struct TYPE_6__ {int const depth; int const shift; } ;
typedef  TYPE_2__ SwsContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int planarToP01xWrapper(SwsContext *c, const uint8_t *src8[],
                               int srcStride[], int srcSliceY,
                               int srcSliceH, uint8_t *dstParam8[],
                               int dstStride[])
{
    const AVPixFmtDescriptor *src_format = av_pix_fmt_desc_get(c->srcFormat);
    const AVPixFmtDescriptor *dst_format = av_pix_fmt_desc_get(c->dstFormat);
    const uint16_t **src = (const uint16_t**)src8;
    uint16_t *dstY = (uint16_t*)(dstParam8[0] + dstStride[0] * srcSliceY);
    uint16_t *dstUV = (uint16_t*)(dstParam8[1] + dstStride[1] * srcSliceY / 2);
    int x, y;

    /* Calculate net shift required for values. */
    const int shift[3] = {
        dst_format->comp[0].depth + dst_format->comp[0].shift -
        src_format->comp[0].depth - src_format->comp[0].shift,
        dst_format->comp[1].depth + dst_format->comp[1].shift -
        src_format->comp[1].depth - src_format->comp[1].shift,
        dst_format->comp[2].depth + dst_format->comp[2].shift -
        src_format->comp[2].depth - src_format->comp[2].shift,
    };

    av_assert0(!(srcStride[0] % 2 || srcStride[1] % 2 || srcStride[2] % 2 ||
                 dstStride[0] % 2 || dstStride[1] % 2));

    for (y = 0; y < srcSliceH; y++) {
        uint16_t *tdstY = dstY;
        const uint16_t *tsrc0 = src[0];
        for (x = c->srcW; x > 0; x--) {
            *tdstY++ = *tsrc0++ << shift[0];
        }
        src[0] += srcStride[0] / 2;
        dstY += dstStride[0] / 2;

        if (!(y & 1)) {
            uint16_t *tdstUV = dstUV;
            const uint16_t *tsrc1 = src[1];
            const uint16_t *tsrc2 = src[2];
            for (x = c->srcW / 2; x > 0; x--) {
                *tdstUV++ = *tsrc1++ << shift[1];
                *tdstUV++ = *tsrc2++ << shift[2];
            }
            src[1] += srcStride[1] / 2;
            src[2] += srcStride[2] / 2;
            dstUV += dstStride[1] / 2;
        }
    }

    return srcSliceH;
}