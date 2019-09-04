#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int h; int w; int /*<<< orphan*/  format; TYPE_1__* dst; } ;
struct TYPE_14__ {int /*<<< orphan*/ * get_cost; } ;
struct TYPE_13__ {int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; } ;
struct TYPE_12__ {void* blocks; } ;
struct TYPE_11__ {int log2_mb_size; int mb_size; int b_width; int b_height; int b_count; scalar_t__ mi_mode; scalar_t__ me_mode; scalar_t__ me_method; scalar_t__ scd_method; void* pixel_refs; void* pixel_weights; void* pixel_mvs; TYPE_3__* frames; int /*<<< orphan*/  search_param; int /*<<< orphan*/  sad; void** mv_table; void* int_blocks; int /*<<< orphan*/  nb_planes; int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; TYPE_5__ me_ctx; } ;
struct TYPE_10__ {TYPE_2__* priv; } ;
typedef  int /*<<< orphan*/  PixelWeights ;
typedef  int /*<<< orphan*/  PixelRefs ;
typedef  int /*<<< orphan*/  PixelMVS ;
typedef  TYPE_2__ MIContext ;
typedef  TYPE_3__ Frame ;
typedef  int /*<<< orphan*/  Block ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVMotionEstContext ;
typedef  TYPE_6__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_ME_METHOD_EPZS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ ME_MODE_BIDIR ; 
 scalar_t__ ME_MODE_BILAT ; 
 scalar_t__ MI_MODE_MCI ; 
 int NB_FRAMES ; 
 scalar_t__ SCD_METHOD_FDIFF ; 
 int av_ceil_log2_c (int) ; 
 int /*<<< orphan*/  av_freep (void**) ; 
 void* av_mallocz_array (int const,int) ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_me_init_context (TYPE_5__*,int,int /*<<< orphan*/ ,int const,int const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_scene_sad_get_fn (int) ; 
 int /*<<< orphan*/  get_sad_ob ; 
 int /*<<< orphan*/  get_sbad_ob ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    MIContext *mi_ctx = inlink->dst->priv;
    AVMotionEstContext *me_ctx = &mi_ctx->me_ctx;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    const int height = inlink->h;
    const int width  = inlink->w;
    int i, ret = 0;

    mi_ctx->log2_chroma_h = desc->log2_chroma_h;
    mi_ctx->log2_chroma_w = desc->log2_chroma_w;

    mi_ctx->nb_planes = av_pix_fmt_count_planes(inlink->format);

    mi_ctx->log2_mb_size = av_ceil_log2_c(mi_ctx->mb_size);
    mi_ctx->mb_size = 1 << mi_ctx->log2_mb_size;

    mi_ctx->b_width  = width >> mi_ctx->log2_mb_size;
    mi_ctx->b_height = height >> mi_ctx->log2_mb_size;
    mi_ctx->b_count = mi_ctx->b_width * mi_ctx->b_height;

    for (i = 0; i < NB_FRAMES; i++) {
        Frame *frame = &mi_ctx->frames[i];
        frame->blocks = av_mallocz_array(mi_ctx->b_count, sizeof(Block));
        if (!frame->blocks)
            return AVERROR(ENOMEM);
    }

    if (mi_ctx->mi_mode == MI_MODE_MCI) {
        mi_ctx->pixel_mvs = av_mallocz_array(width * height, sizeof(PixelMVS));
        mi_ctx->pixel_weights = av_mallocz_array(width * height, sizeof(PixelWeights));
        mi_ctx->pixel_refs = av_mallocz_array(width * height, sizeof(PixelRefs));
        if (!mi_ctx->pixel_mvs || !mi_ctx->pixel_weights || !mi_ctx->pixel_refs) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        if (mi_ctx->me_mode == ME_MODE_BILAT)
            if (!(mi_ctx->int_blocks = av_mallocz_array(mi_ctx->b_count, sizeof(Block))))
                return AVERROR(ENOMEM);

        if (mi_ctx->me_method == AV_ME_METHOD_EPZS) {
            for (i = 0; i < 3; i++) {
                mi_ctx->mv_table[i] = av_mallocz_array(mi_ctx->b_count, sizeof(*mi_ctx->mv_table[0]));
                if (!mi_ctx->mv_table[i])
                    return AVERROR(ENOMEM);
            }
        }
    }

    if (mi_ctx->scd_method == SCD_METHOD_FDIFF) {
        mi_ctx->sad = ff_scene_sad_get_fn(8);
        if (!mi_ctx->sad)
            return AVERROR(EINVAL);
    }

    ff_me_init_context(me_ctx, mi_ctx->mb_size, mi_ctx->search_param, width, height, 0, (mi_ctx->b_width - 1) << mi_ctx->log2_mb_size, 0, (mi_ctx->b_height - 1) << mi_ctx->log2_mb_size);

    if (mi_ctx->me_mode == ME_MODE_BIDIR)
        me_ctx->get_cost = &get_sad_ob;
    else if (mi_ctx->me_mode == ME_MODE_BILAT)
        me_ctx->get_cost = &get_sbad_ob;

    return 0;
fail:
    for (i = 0; i < NB_FRAMES; i++)
        av_freep(&mi_ctx->frames[i].blocks);
    av_freep(&mi_ctx->pixel_mvs);
    av_freep(&mi_ctx->pixel_weights);
    av_freep(&mi_ctx->pixel_refs);
    return ret;
}