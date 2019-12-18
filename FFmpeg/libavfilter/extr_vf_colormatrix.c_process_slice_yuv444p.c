#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int c2; int c3; int c4; int c5; int c6; int c7; TYPE_2__* dst; TYPE_2__* src; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_4__ {int height; int width; int* linesize; unsigned char** data; } ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 unsigned char CB (int const) ; 

__attribute__((used)) static int process_slice_yuv444p(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    const ThreadData *td = arg;
    const AVFrame *src = td->src;
    AVFrame *dst = td->dst;
    const int height = src->height;
    const int width = src->width;
    const int slice_start = (height *  jobnr   ) / nb_jobs;
    const int slice_end   = (height * (jobnr+1)) / nb_jobs;
    const int src_pitchY  = src->linesize[0];
    const int src_pitchUV = src->linesize[1];
    const unsigned char *srcpU = src->data[1] + slice_start * src_pitchUV;
    const unsigned char *srcpV = src->data[2] + slice_start * src_pitchUV;
    const unsigned char *srcpY = src->data[0] + slice_start * src_pitchY;
    const int dst_pitchY  = dst->linesize[0];
    const int dst_pitchUV = dst->linesize[1];
    unsigned char *dstpU = dst->data[1] + slice_start * dst_pitchUV;
    unsigned char *dstpV = dst->data[2] + slice_start * dst_pitchUV;
    unsigned char *dstpY = dst->data[0] + slice_start * dst_pitchY;
    const int c2 = td->c2;
    const int c3 = td->c3;
    const int c4 = td->c4;
    const int c5 = td->c5;
    const int c6 = td->c6;
    const int c7 = td->c7;
    int x, y;

    for (y = slice_start; y < slice_end; y++) {
        for (x = 0; x < width; x++) {
            const int u = srcpU[x] - 128;
            const int v = srcpV[x] - 128;
            const int uvval = c2 * u + c3 * v + 1081344;
            dstpY[x] = CB((65536 * (srcpY[x] - 16) + uvval) >> 16);
            dstpU[x] = CB((c4 * u + c5 * v + 8421376) >> 16);
            dstpV[x] = CB((c6 * u + c7 * v + 8421376) >> 16);
        }
        srcpY += src_pitchY;
        dstpY += dst_pitchY;
        srcpU += src_pitchUV;
        srcpV += src_pitchUV;
        dstpU += dst_pitchUV;
        dstpV += dst_pitchUV;
    }

    return 0;
}