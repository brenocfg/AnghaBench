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
typedef  int uint16_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_8__ {int flags; TYPE_1__* comp; } ;
struct TYPE_7__ {scalar_t__ srcFormat; } ;
struct TYPE_6__ {int depth; } ;
typedef  TYPE_2__ SwsContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_FLOAT ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 int FFMIN (int,int) ; 
 TYPE_3__* av_pix_fmt_desc_get (scalar_t__) ; 
 scalar_t__ isAnyRGB (scalar_t__) ; 

__attribute__((used)) static void hScale16To19_c(SwsContext *c, int16_t *_dst, int dstW,
                           const uint8_t *_src, const int16_t *filter,
                           const int32_t *filterPos, int filterSize)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(c->srcFormat);
    int i;
    int32_t *dst        = (int32_t *) _dst;
    const uint16_t *src = (const uint16_t *) _src;
    int bits            = desc->comp[0].depth - 1;
    int sh              = bits - 4;

    if ((isAnyRGB(c->srcFormat) || c->srcFormat==AV_PIX_FMT_PAL8) && desc->comp[0].depth<16) {
        sh = 9;
    } else if (desc->flags & AV_PIX_FMT_FLAG_FLOAT) { /* float input are process like uint 16bpc */
        sh = 16 - 1 - 4;
    }

    for (i = 0; i < dstW; i++) {
        int j;
        int srcPos = filterPos[i];
        int val    = 0;

        for (j = 0; j < filterSize; j++) {
            val += src[srcPos + j] * filter[filterSize * i + j];
        }
        // filter=14 bit, input=16 bit, output=30 bit, >> 11 makes 19 bit
        dst[i] = FFMIN(val >> sh, (1 << 19) - 1);
    }
}