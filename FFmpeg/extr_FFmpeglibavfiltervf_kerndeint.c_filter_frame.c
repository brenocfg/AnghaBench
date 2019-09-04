#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  srcppp ;
typedef  int /*<<< orphan*/  srcpnn ;
typedef  int /*<<< orphan*/  prvppp ;
struct TYPE_17__ {int h; scalar_t__ format; int /*<<< orphan*/  w; TYPE_1__* dst; } ;
struct TYPE_16__ {int** data; int* linesize; scalar_t__ interlaced_frame; } ;
struct TYPE_15__ {int thresh; int order; int map; int sharp; int twoway; int is_packed_rgb; int* tmp_bwidth; int* tmp_linesize; int** tmp_data; int /*<<< orphan*/  vsub; int /*<<< orphan*/  frame; } ;
struct TYPE_14__ {TYPE_4__** outputs; TYPE_2__* priv; } ;
typedef  TYPE_2__ KerndeintContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 scalar_t__ AV_PIX_FMT_YUYV422 ; 
 int /*<<< orphan*/  AV_WB32 (int*,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int const abs (int) ; 
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 int /*<<< orphan*/  av_image_copy_plane (int*,int,int const*,int,int,int) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* ff_get_video_buffer (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *inpic)
{
    KerndeintContext *kerndeint = inlink->dst->priv;
    AVFilterLink *outlink = inlink->dst->outputs[0];
    AVFrame *outpic;
    const uint8_t *prvp;   ///< Previous field's pixel line number n
    const uint8_t *prvpp;  ///< Previous field's pixel line number (n - 1)
    const uint8_t *prvpn;  ///< Previous field's pixel line number (n + 1)
    const uint8_t *prvppp; ///< Previous field's pixel line number (n - 2)
    const uint8_t *prvpnn; ///< Previous field's pixel line number (n + 2)
    const uint8_t *prvp4p; ///< Previous field's pixel line number (n - 4)
    const uint8_t *prvp4n; ///< Previous field's pixel line number (n + 4)

    const uint8_t *srcp;   ///< Current field's pixel line number n
    const uint8_t *srcpp;  ///< Current field's pixel line number (n - 1)
    const uint8_t *srcpn;  ///< Current field's pixel line number (n + 1)
    const uint8_t *srcppp; ///< Current field's pixel line number (n - 2)
    const uint8_t *srcpnn; ///< Current field's pixel line number (n + 2)
    const uint8_t *srcp3p; ///< Current field's pixel line number (n - 3)
    const uint8_t *srcp3n; ///< Current field's pixel line number (n + 3)
    const uint8_t *srcp4p; ///< Current field's pixel line number (n - 4)
    const uint8_t *srcp4n; ///< Current field's pixel line number (n + 4)

    uint8_t *dstp, *dstp_saved;
    const uint8_t *srcp_saved;

    int src_linesize, psrc_linesize, dst_linesize, bwidth;
    int x, y, plane, val, hi, lo, g, h, n = kerndeint->frame++;
    double valf;

    const int thresh = kerndeint->thresh;
    const int order  = kerndeint->order;
    const int map    = kerndeint->map;
    const int sharp  = kerndeint->sharp;
    const int twoway = kerndeint->twoway;

    const int is_packed_rgb = kerndeint->is_packed_rgb;

    outpic = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!outpic) {
        av_frame_free(&inpic);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(outpic, inpic);
    outpic->interlaced_frame = 0;

    for (plane = 0; plane < 4 && inpic->data[plane] && inpic->linesize[plane]; plane++) {
        h = plane == 0 ? inlink->h : AV_CEIL_RSHIFT(inlink->h, kerndeint->vsub);
        bwidth = kerndeint->tmp_bwidth[plane];

        srcp_saved        = inpic->data[plane];
        src_linesize      = inpic->linesize[plane];
        psrc_linesize     = kerndeint->tmp_linesize[plane];
        dstp_saved        = outpic->data[plane];
        dst_linesize      = outpic->linesize[plane];
        srcp              = srcp_saved + (1 - order) * src_linesize;
        dstp              = dstp_saved + (1 - order) * dst_linesize;

        for (y = 0; y < h; y += 2) {
            memcpy(dstp, srcp, bwidth);
            srcp += 2 * src_linesize;
            dstp += 2 * dst_linesize;
        }

        // Copy through the lines that will be missed below.
        memcpy(dstp_saved + order            * dst_linesize, srcp_saved + (1 -     order) * src_linesize, bwidth);
        memcpy(dstp_saved + (2 + order    )  * dst_linesize, srcp_saved + (3 -     order) * src_linesize, bwidth);
        memcpy(dstp_saved + (h - 2 + order)  * dst_linesize, srcp_saved + (h - 1 - order) * src_linesize, bwidth);
        memcpy(dstp_saved + (h - 4 + order)  * dst_linesize, srcp_saved + (h - 3 - order) * src_linesize, bwidth);

        /* For the other field choose adaptively between using the previous field
           or the interpolant from the current field. */
        prvp   = kerndeint->tmp_data[plane] + 5 * psrc_linesize - (1 - order) * psrc_linesize;
        prvpp  = prvp - psrc_linesize;
        prvppp = prvp - 2 * psrc_linesize;
        prvp4p = prvp - 4 * psrc_linesize;
        prvpn  = prvp + psrc_linesize;
        prvpnn = prvp + 2 * psrc_linesize;
        prvp4n = prvp + 4 * psrc_linesize;

        srcp   = srcp_saved + 5 * src_linesize - (1 - order) * src_linesize;
        srcpp  = srcp - src_linesize;
        srcppp = srcp - 2 * src_linesize;
        srcp3p = srcp - 3 * src_linesize;
        srcp4p = srcp - 4 * src_linesize;

        srcpn  = srcp + src_linesize;
        srcpnn = srcp + 2 * src_linesize;
        srcp3n = srcp + 3 * src_linesize;
        srcp4n = srcp + 4 * src_linesize;

        dstp   = dstp_saved + 5 * dst_linesize - (1 - order) * dst_linesize;

        for (y = 5 - (1 - order); y <= h - 5 - (1 - order); y += 2) {
            for (x = 0; x < bwidth; x++) {
                if (thresh == 0 || n == 0 ||
                    (abs((int)prvp[x]  - (int)srcp[x])  > thresh) ||
                    (abs((int)prvpp[x] - (int)srcpp[x]) > thresh) ||
                    (abs((int)prvpn[x] - (int)srcpn[x]) > thresh)) {
                    if (map) {
                        g = x & ~3;

                        if (is_packed_rgb) {
                            AV_WB32(dstp + g, 0xffffffff);
                            x = g + 3;
                        } else if (inlink->format == AV_PIX_FMT_YUYV422) {
                            // y <- 235, u <- 128, y <- 235, v <- 128
                            AV_WB32(dstp + g, 0xeb80eb80);
                            x = g + 3;
                        } else {
                            dstp[x] = plane == 0 ? 235 : 128;
                        }
                    } else {
                        if (is_packed_rgb) {
                            hi = 255;
                            lo = 0;
                        } else if (inlink->format == AV_PIX_FMT_YUYV422) {
                            hi = x & 1 ? 240 : 235;
                            lo = 16;
                        } else {
                            hi = plane == 0 ? 235 : 240;
                            lo = 16;
                        }

                        if (sharp) {
                            if (twoway) {
                                valf = + 0.526 * ((int)srcpp[x] + (int)srcpn[x])
                                    + 0.170 * ((int)srcp[x] + (int)prvp[x])
                                    - 0.116 * ((int)srcppp[x] + (int)srcpnn[x] + (int)prvppp[x] + (int)prvpnn[x])
                                    - 0.026 * ((int)srcp3p[x] + (int)srcp3n[x])
                                    + 0.031 * ((int)srcp4p[x] + (int)srcp4n[x] + (int)prvp4p[x] + (int)prvp4n[x]);
                            } else {
                                valf = + 0.526 * ((int)srcpp[x] + (int)srcpn[x])
                                    + 0.170 * ((int)prvp[x])
                                    - 0.116 * ((int)prvppp[x] + (int)prvpnn[x])
                                    - 0.026 * ((int)srcp3p[x] + (int)srcp3n[x])
                                    + 0.031 * ((int)prvp4p[x] + (int)prvp4p[x]);
                            }
                            dstp[x] = av_clip(valf, lo, hi);
                        } else {
                            if (twoway) {
                                val = (8 * ((int)srcpp[x] + (int)srcpn[x]) + 2 * ((int)srcp[x] + (int)prvp[x])
                                       - (int)(srcppp[x]) - (int)(srcpnn[x])
                                       - (int)(prvppp[x]) - (int)(prvpnn[x])) >> 4;
                            } else {
                                val = (8 * ((int)srcpp[x] + (int)srcpn[x]) + 2 * ((int)prvp[x])
                                       - (int)(prvppp[x]) - (int)(prvpnn[x])) >> 4;
                            }
                            dstp[x] = av_clip(val, lo, hi);
                        }
                    }
                } else {
                    dstp[x] = srcp[x];
                }
            }
            prvp   += 2 * psrc_linesize;
            prvpp  += 2 * psrc_linesize;
            prvppp += 2 * psrc_linesize;
            prvpn  += 2 * psrc_linesize;
            prvpnn += 2 * psrc_linesize;
            prvp4p += 2 * psrc_linesize;
            prvp4n += 2 * psrc_linesize;
            srcp   += 2 * src_linesize;
            srcpp  += 2 * src_linesize;
            srcppp += 2 * src_linesize;
            srcp3p += 2 * src_linesize;
            srcp4p += 2 * src_linesize;
            srcpn  += 2 * src_linesize;
            srcpnn += 2 * src_linesize;
            srcp3n += 2 * src_linesize;
            srcp4n += 2 * src_linesize;
            dstp   += 2 * dst_linesize;
        }

        srcp = inpic->data[plane];
        dstp = kerndeint->tmp_data[plane];
        av_image_copy_plane(dstp, psrc_linesize, srcp, src_linesize, bwidth, h);
    }

    av_frame_free(&inpic);
    return ff_filter_frame(outlink, outpic);
}