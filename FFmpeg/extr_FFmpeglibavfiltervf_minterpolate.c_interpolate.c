#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_19__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_28__ {TYPE_4__* priv; TYPE_7__** outputs; } ;
struct TYPE_21__ {int num; int den; } ;
struct TYPE_27__ {TYPE_1__ time_base; TYPE_8__* dst; } ;
struct TYPE_26__ {int width; int height; int** data; int* linesize; int /*<<< orphan*/  pts; } ;
struct TYPE_25__ {int /*<<< orphan*/  sb; } ;
struct TYPE_24__ {int mi_mode; int nb_planes; int b_height; int b_width; int log2_mb_size; TYPE_5__* int_blocks; TYPE_3__* frames; TYPE_2__* pixel_refs; int /*<<< orphan*/  me_mode; int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; scalar_t__ scene_changed; } ;
struct TYPE_23__ {TYPE_19__* avf; } ;
struct TYPE_22__ {int /*<<< orphan*/  nb; } ;
struct TYPE_20__ {int pts; int** data; int* linesize; int height; int width; } ;
typedef  TYPE_4__ MIContext ;
typedef  TYPE_5__ Block ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVFilterLink ;
typedef  TYPE_8__ AVFilterContext ;

/* Variables and functions */
 int ALPHA_MAX ; 
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_MODE_BIDIR ; 
 int /*<<< orphan*/  ME_MODE_BILAT ; 
#define  MI_MODE_BLEND 130 
#define  MI_MODE_DUP 129 
#define  MI_MODE_MCI 128 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_frame_copy (TYPE_6__*,TYPE_19__*) ; 
 int av_rescale (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bidirectional_obmc (TYPE_4__*,int) ; 
 int /*<<< orphan*/  bilateral_obmc (TYPE_4__*,TYPE_5__*,int,int,int) ; 
 int /*<<< orphan*/  set_frame_data (TYPE_4__*,int,TYPE_6__*) ; 
 int /*<<< orphan*/  var_size_bmc (TYPE_4__*,TYPE_5__*,int,int,int,int) ; 

__attribute__((used)) static void interpolate(AVFilterLink *inlink, AVFrame *avf_out)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    MIContext *mi_ctx = ctx->priv;
    int x, y;
    int plane, alpha;
    int64_t pts;

    pts = av_rescale(avf_out->pts, (int64_t) ALPHA_MAX * outlink->time_base.num * inlink->time_base.den,
                                   (int64_t)             outlink->time_base.den * inlink->time_base.num);

    alpha = (pts - mi_ctx->frames[1].avf->pts * ALPHA_MAX) / (mi_ctx->frames[2].avf->pts - mi_ctx->frames[1].avf->pts);
    alpha = av_clip(alpha, 0, ALPHA_MAX);

    if (alpha == 0 || alpha == ALPHA_MAX) {
        av_frame_copy(avf_out, alpha ? mi_ctx->frames[2].avf : mi_ctx->frames[1].avf);
        return;
    }

    if (mi_ctx->scene_changed) {
        /* duplicate frame */
        av_frame_copy(avf_out, alpha > ALPHA_MAX / 2 ? mi_ctx->frames[2].avf : mi_ctx->frames[1].avf);
        return;
    }

    switch(mi_ctx->mi_mode) {
        case MI_MODE_DUP:
            av_frame_copy(avf_out, alpha > ALPHA_MAX / 2 ? mi_ctx->frames[2].avf : mi_ctx->frames[1].avf);

            break;
        case MI_MODE_BLEND:
            for (plane = 0; plane < mi_ctx->nb_planes; plane++) {
                int width = avf_out->width;
                int height = avf_out->height;

                if (plane == 1 || plane == 2) {
                    width = AV_CEIL_RSHIFT(width, mi_ctx->log2_chroma_w);
                    height = AV_CEIL_RSHIFT(height, mi_ctx->log2_chroma_h);
                }

                for (y = 0; y < height; y++) {
                    for (x = 0; x < width; x++) {
                        avf_out->data[plane][x + y * avf_out->linesize[plane]] =
                            (alpha  * mi_ctx->frames[2].avf->data[plane][x + y * mi_ctx->frames[2].avf->linesize[plane]] +
                             (ALPHA_MAX - alpha) * mi_ctx->frames[1].avf->data[plane][x + y * mi_ctx->frames[1].avf->linesize[plane]] + 512) >> 10;
                    }
                }
            }

            break;
        case MI_MODE_MCI:
            if (mi_ctx->me_mode == ME_MODE_BIDIR) {
                bidirectional_obmc(mi_ctx, alpha);
                set_frame_data(mi_ctx, alpha, avf_out);

            } else if (mi_ctx->me_mode == ME_MODE_BILAT) {
                int mb_x, mb_y;
                Block *block;

                for (y = 0; y < mi_ctx->frames[0].avf->height; y++)
                    for (x = 0; x < mi_ctx->frames[0].avf->width; x++)
                        mi_ctx->pixel_refs[x + y * mi_ctx->frames[0].avf->width].nb = 0;

                for (mb_y = 0; mb_y < mi_ctx->b_height; mb_y++)
                    for (mb_x = 0; mb_x < mi_ctx->b_width; mb_x++) {
                        block = &mi_ctx->int_blocks[mb_x + mb_y * mi_ctx->b_width];

                        if (block->sb)
                            var_size_bmc(mi_ctx, block, mb_x << mi_ctx->log2_mb_size, mb_y << mi_ctx->log2_mb_size, mi_ctx->log2_mb_size, alpha);

                        bilateral_obmc(mi_ctx, block, mb_x, mb_y, alpha);

                    }

                set_frame_data(mi_ctx, alpha, avf_out);
            }

            break;
    }
}