#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_20__ {TYPE_4__** outputs; TYPE_2__* priv; } ;
struct TYPE_19__ {int h; int /*<<< orphan*/  w; TYPE_5__* dst; } ;
struct TYPE_18__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_17__ {int step; int bpp; int nb_comp; int linesize; int /*<<< orphan*/ * rgba_map; TYPE_1__* range; } ;
struct TYPE_16__ {int in_min; int in_max; int out_min; int out_max; } ;
typedef  TYPE_1__ Range ;
typedef  TYPE_2__ ColorLevelsContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int /*<<< orphan*/  const) ; 
 int FFMIN (int,int /*<<< orphan*/  const) ; 
 int UINT16_MAX ; 
 int UINT8_MAX ; 
 int /*<<< orphan*/  av_clip_uint16 (double) ; 
 int /*<<< orphan*/  av_clip_uint8 (double) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_3__*) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* ff_get_video_buffer (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int lrint (int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    ColorLevelsContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    const int step = s->step;
    AVFrame *out;
    int x, y, i;

    if (av_frame_is_writable(in)) {
        out = in;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }

    switch (s->bpp) {
    case 1:
        for (i = 0; i < s->nb_comp; i++) {
            Range *r = &s->range[i];
            const uint8_t offset = s->rgba_map[i];
            const uint8_t *srcrow = in->data[0];
            uint8_t *dstrow = out->data[0];
            int imin = lrint(r->in_min  * UINT8_MAX);
            int imax = lrint(r->in_max  * UINT8_MAX);
            int omin = lrint(r->out_min * UINT8_MAX);
            int omax = lrint(r->out_max * UINT8_MAX);
            double coeff;

            if (imin < 0) {
                imin = UINT8_MAX;
                for (y = 0; y < inlink->h; y++) {
                    const uint8_t *src = srcrow;

                    for (x = 0; x < s->linesize; x += step)
                        imin = FFMIN(imin, src[x + offset]);
                    srcrow += in->linesize[0];
                }
            }
            if (imax < 0) {
                srcrow = in->data[0];
                imax = 0;
                for (y = 0; y < inlink->h; y++) {
                    const uint8_t *src = srcrow;

                    for (x = 0; x < s->linesize; x += step)
                        imax = FFMAX(imax, src[x + offset]);
                    srcrow += in->linesize[0];
                }
            }

            srcrow = in->data[0];
            coeff = (omax - omin) / (double)(imax - imin);
            for (y = 0; y < inlink->h; y++) {
                const uint8_t *src = srcrow;
                uint8_t *dst = dstrow;

                for (x = 0; x < s->linesize; x += step)
                    dst[x + offset] = av_clip_uint8((src[x + offset] - imin) * coeff + omin);
                dstrow += out->linesize[0];
                srcrow += in->linesize[0];
            }
        }
        break;
    case 2:
        for (i = 0; i < s->nb_comp; i++) {
            Range *r = &s->range[i];
            const uint8_t offset = s->rgba_map[i];
            const uint8_t *srcrow = in->data[0];
            uint8_t *dstrow = out->data[0];
            int imin = lrint(r->in_min  * UINT16_MAX);
            int imax = lrint(r->in_max  * UINT16_MAX);
            int omin = lrint(r->out_min * UINT16_MAX);
            int omax = lrint(r->out_max * UINT16_MAX);
            double coeff;

            if (imin < 0) {
                imin = UINT16_MAX;
                for (y = 0; y < inlink->h; y++) {
                    const uint16_t *src = (const uint16_t *)srcrow;

                    for (x = 0; x < s->linesize; x += step)
                        imin = FFMIN(imin, src[x + offset]);
                    srcrow += in->linesize[0];
                }
            }
            if (imax < 0) {
                srcrow = in->data[0];
                imax = 0;
                for (y = 0; y < inlink->h; y++) {
                    const uint16_t *src = (const uint16_t *)srcrow;

                    for (x = 0; x < s->linesize; x += step)
                        imax = FFMAX(imax, src[x + offset]);
                    srcrow += in->linesize[0];
                }
            }

            srcrow = in->data[0];
            coeff = (omax - omin) / (double)(imax - imin);
            for (y = 0; y < inlink->h; y++) {
                const uint16_t *src = (const uint16_t*)srcrow;
                uint16_t *dst = (uint16_t *)dstrow;

                for (x = 0; x < s->linesize; x += step)
                    dst[x + offset] = av_clip_uint16((src[x + offset] - imin) * coeff + omin);
                dstrow += out->linesize[0];
                srcrow += in->linesize[0];
            }
        }
    }

    if (in != out)
        av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}