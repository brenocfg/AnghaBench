#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  size_t uint16_t ;
typedef  unsigned int int64_t ;
struct TYPE_23__ {TYPE_7__** outputs; TYPE_5__* priv; } ;
struct TYPE_22__ {int /*<<< orphan*/  w; int /*<<< orphan*/  h; TYPE_8__* dst; } ;
struct TYPE_21__ {size_t** data; int* linesize; int /*<<< orphan*/  pts; } ;
struct TYPE_20__ {int histogram_size; int const* bg_color; int mult; int ncomp; int* planeheight; int* planewidth; int components; int display_mode; int level_height; int scale_height; unsigned int* histogram; int dncomp; size_t* fg_color; scalar_t__ levels_mode; TYPE_2__* desc; TYPE_3__* odesc; } ;
struct TYPE_19__ {size_t plane; } ;
struct TYPE_18__ {TYPE_4__* comp; int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; } ;
struct TYPE_17__ {TYPE_1__* comp; } ;
struct TYPE_16__ {int plane; } ;
typedef  TYPE_5__ HistogramContext ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVFilterLink ;
typedef  TYPE_8__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WN16 (size_t*,int const) ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int FFMAX (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_6__**) ; 
 int ff_filter_frame (TYPE_7__*,TYPE_6__*) ; 
 TYPE_6__* ff_get_video_buffer (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double log2 (unsigned int) ; 
 int lrint (int) ; 
 int /*<<< orphan*/  memset (size_t*,int const,int const) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    HistogramContext *h   = inlink->dst->priv;
    AVFilterContext *ctx  = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    int i, j, k, l, m;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }

    out->pts = in->pts;

    for (k = 0; k < 4 && out->data[k]; k++) {
        const int is_chroma = (k == 1 || k == 2);
        const int dst_h = AV_CEIL_RSHIFT(outlink->h, (is_chroma ? h->odesc->log2_chroma_h : 0));
        const int dst_w = AV_CEIL_RSHIFT(outlink->w, (is_chroma ? h->odesc->log2_chroma_w : 0));

        if (h->histogram_size <= 256) {
            for (i = 0; i < dst_h ; i++)
                memset(out->data[h->odesc->comp[k].plane] +
                       i * out->linesize[h->odesc->comp[k].plane],
                       h->bg_color[k], dst_w);
        } else {
            const int mult = h->mult;

            for (i = 0; i < dst_h ; i++)
                for (j = 0; j < dst_w; j++)
                    AV_WN16(out->data[h->odesc->comp[k].plane] +
                        i * out->linesize[h->odesc->comp[k].plane] + j * 2,
                        h->bg_color[k] * mult);
        }
    }

    for (m = 0, k = 0; k < h->ncomp; k++) {
        const int p = h->desc->comp[k].plane;
        const int height = h->planeheight[p];
        const int width = h->planewidth[p];
        double max_hval_log;
        unsigned max_hval = 0;
        int start, startx;

        if (!((1 << k) & h->components))
            continue;
        startx = m * h->histogram_size * (h->display_mode == 1);
        start = m++ * (h->level_height + h->scale_height) * (h->display_mode == 2);

        if (h->histogram_size <= 256) {
            for (i = 0; i < height; i++) {
                const uint8_t *src = in->data[p] + i * in->linesize[p];
                for (j = 0; j < width; j++)
                    h->histogram[src[j]]++;
            }
        } else {
            for (i = 0; i < height; i++) {
                const uint16_t *src = (const uint16_t *)(in->data[p] + i * in->linesize[p]);
                for (j = 0; j < width; j++)
                    h->histogram[src[j]]++;
            }
        }

        for (i = 0; i < h->histogram_size; i++)
            max_hval = FFMAX(max_hval, h->histogram[i]);
        max_hval_log = log2(max_hval + 1);

        for (i = 0; i < h->histogram_size; i++) {
            int col_height;

            if (h->levels_mode)
                col_height = lrint(h->level_height * (1. - (log2(h->histogram[i] + 1) / max_hval_log)));
            else
                col_height = h->level_height - (h->histogram[i] * (int64_t)h->level_height + max_hval - 1) / max_hval;

            if (h->histogram_size <= 256) {
                for (j = h->level_height - 1; j >= col_height; j--) {
                    if (h->display_mode) {
                        for (l = 0; l < h->dncomp; l++)
                            out->data[l][(j + start) * out->linesize[l] + startx + i] = h->fg_color[l];
                    } else {
                        out->data[p][(j + start) * out->linesize[p] + startx + i] = 255;
                    }
                }
                for (j = h->level_height + h->scale_height - 1; j >= h->level_height; j--)
                    out->data[p][(j + start) * out->linesize[p] + startx + i] = i;
            } else {
                const int mult = h->mult;

                for (j = h->level_height - 1; j >= col_height; j--) {
                    if (h->display_mode) {
                        for (l = 0; l < h->dncomp; l++)
                            AV_WN16(out->data[l] + (j + start) * out->linesize[l] + startx * 2 + i * 2, h->fg_color[l] * mult);
                    } else {
                        AV_WN16(out->data[p] + (j + start) * out->linesize[p] + startx * 2 + i * 2, 255 * mult);
                    }
                }
                for (j = h->level_height + h->scale_height - 1; j >= h->level_height; j--)
                    AV_WN16(out->data[p] + (j + start) * out->linesize[p] + startx * 2 + i * 2, i);
            }
        }

        memset(h->histogram, 0, h->histogram_size * sizeof(unsigned));
    }

    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}