#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {size_t** data; int* linesize; int width; int height; } ;
struct TYPE_6__ {int* palette; unsigned int total_mean_err; int /*<<< orphan*/  trans_thresh; } ;
typedef  TYPE_1__ PaletteUseContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned int,float const) ; 
 scalar_t__ diff (size_t const*,size_t const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void debug_mean_error(PaletteUseContext *s, const AVFrame *in1,
                             const AVFrame *in2, int frame_count)
{
    int x, y;
    const uint32_t *palette = s->palette;
    uint32_t *src1 = (uint32_t *)in1->data[0];
    uint8_t  *src2 =             in2->data[0];
    const int src1_linesize = in1->linesize[0] >> 2;
    const int src2_linesize = in2->linesize[0];
    const float div = in1->width * in1->height * 3;
    unsigned mean_err = 0;

    for (y = 0; y < in1->height; y++) {
        for (x = 0; x < in1->width; x++) {
            const uint32_t c1 = src1[x];
            const uint32_t c2 = palette[src2[x]];
            const uint8_t argb1[] = {0xff, c1 >> 16 & 0xff, c1 >> 8 & 0xff, c1 & 0xff};
            const uint8_t argb2[] = {0xff, c2 >> 16 & 0xff, c2 >> 8 & 0xff, c2 & 0xff};
            mean_err += diff(argb1, argb2, s->trans_thresh);
        }
        src1 += src1_linesize;
        src2 += src2_linesize;
    }

    s->total_mean_err += mean_err;

    av_log(NULL, AV_LOG_INFO, "MEP:%.3f TotalMEP:%.3f\n",
           mean_err / div, s->total_mean_err / (div * frame_count));
}