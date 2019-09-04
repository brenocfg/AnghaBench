#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct ThreadData {int /*<<< orphan*/  out_ss_h; int /*<<< orphan*/  in_ss_h; int /*<<< orphan*/ * out_linesize; int /*<<< orphan*/ * in_linesize; TYPE_5__* out; TYPE_5__* in; } ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_32__ {TYPE_2__* internal; TYPE_3__* priv; TYPE_6__** outputs; } ;
struct TYPE_31__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_7__* dst; } ;
struct TYPE_30__ {int width; int height; scalar_t__ color_primaries; scalar_t__ color_trc; scalar_t__ colorspace; scalar_t__ color_range; int /*<<< orphan*/  format; int /*<<< orphan*/ * linesize; } ;
struct TYPE_29__ {int log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; TYPE_1__* comp; } ;
struct TYPE_28__ {scalar_t__ user_prm; int user_all; scalar_t__ user_trc; scalar_t__ user_csp; scalar_t__ user_rng; unsigned int rgb_sz; int rgb_stride; scalar_t__ yuv2yuv_passthrough; int /*<<< orphan*/ *** dither_scratch_base; int /*<<< orphan*/ ** rgb; int /*<<< orphan*/ *** dither_scratch; } ;
struct TYPE_27__ {int /*<<< orphan*/  (* execute ) (TYPE_7__*,int /*<<< orphan*/ ,struct ThreadData*,int /*<<< orphan*/ *,size_t) ;} ;
struct TYPE_26__ {int depth; } ;
typedef  TYPE_3__ ColorSpaceContext ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterLink ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AVCOL_PRI_UNSPECIFIED ; 
 scalar_t__ AVCOL_RANGE_UNSPECIFIED ; 
 scalar_t__ AVCOL_SPC_UNSPECIFIED ; 
 scalar_t__ AVCOL_TRC_BT2020_10 ; 
 scalar_t__ AVCOL_TRC_BT2020_12 ; 
 scalar_t__ AVCOL_TRC_UNSPECIFIED ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_NB ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int) ; 
 size_t FFMIN (int,int /*<<< orphan*/ ) ; 
 int av_frame_copy (TYPE_5__*,TYPE_5__*) ; 
 int av_frame_copy_props (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_5__**) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 void* av_malloc (int) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert ; 
 int create_filtergraph (TYPE_7__*,TYPE_5__*,TYPE_5__*) ; 
 scalar_t__* default_csp ; 
 scalar_t__* default_prm ; 
 scalar_t__* default_trc ; 
 int ff_filter_frame (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_7__*) ; 
 TYPE_5__* ff_get_video_buffer (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,struct ThreadData*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  uninit (TYPE_7__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *link, AVFrame *in)
{
    AVFilterContext *ctx = link->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    ColorSpaceContext *s = ctx->priv;
    // FIXME if yuv2yuv_passthrough, don't get a new buffer but use the
    // input one if it is writable *OR* the actual literal values of in_*
    // and out_* are identical (not just their respective properties)
    AVFrame *out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    int res;
    ptrdiff_t rgb_stride = FFALIGN(in->width * sizeof(int16_t), 32);
    unsigned rgb_sz = rgb_stride * in->height;
    struct ThreadData td;

    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    res = av_frame_copy_props(out, in);
    if (res < 0) {
        av_frame_free(&in);
        return res;
    }

    out->color_primaries = s->user_prm == AVCOL_PRI_UNSPECIFIED ?
                           default_prm[FFMIN(s->user_all, CS_NB)] : s->user_prm;
    if (s->user_trc == AVCOL_TRC_UNSPECIFIED) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(out->format);

        out->color_trc   = default_trc[FFMIN(s->user_all, CS_NB)];
        if (out->color_trc == AVCOL_TRC_BT2020_10 && desc && desc->comp[0].depth >= 12)
            out->color_trc = AVCOL_TRC_BT2020_12;
    } else {
        out->color_trc   = s->user_trc;
    }
    out->colorspace      = s->user_csp == AVCOL_SPC_UNSPECIFIED ?
                           default_csp[FFMIN(s->user_all, CS_NB)] : s->user_csp;
    out->color_range     = s->user_rng == AVCOL_RANGE_UNSPECIFIED ?
                           in->color_range : s->user_rng;
    if (rgb_sz != s->rgb_sz) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(out->format);
        int uvw = in->width >> desc->log2_chroma_w;

        av_freep(&s->rgb[0]);
        av_freep(&s->rgb[1]);
        av_freep(&s->rgb[2]);
        s->rgb_sz = 0;
        av_freep(&s->dither_scratch_base[0][0]);
        av_freep(&s->dither_scratch_base[0][1]);
        av_freep(&s->dither_scratch_base[1][0]);
        av_freep(&s->dither_scratch_base[1][1]);
        av_freep(&s->dither_scratch_base[2][0]);
        av_freep(&s->dither_scratch_base[2][1]);

        s->rgb[0] = av_malloc(rgb_sz);
        s->rgb[1] = av_malloc(rgb_sz);
        s->rgb[2] = av_malloc(rgb_sz);
        s->dither_scratch_base[0][0] =
            av_malloc(sizeof(*s->dither_scratch_base[0][0]) * (in->width + 4));
        s->dither_scratch_base[0][1] =
            av_malloc(sizeof(*s->dither_scratch_base[0][1]) * (in->width + 4));
        s->dither_scratch_base[1][0] =
            av_malloc(sizeof(*s->dither_scratch_base[1][0]) * (uvw + 4));
        s->dither_scratch_base[1][1] =
            av_malloc(sizeof(*s->dither_scratch_base[1][1]) * (uvw + 4));
        s->dither_scratch_base[2][0] =
            av_malloc(sizeof(*s->dither_scratch_base[2][0]) * (uvw + 4));
        s->dither_scratch_base[2][1] =
            av_malloc(sizeof(*s->dither_scratch_base[2][1]) * (uvw + 4));
        s->dither_scratch[0][0] = &s->dither_scratch_base[0][0][1];
        s->dither_scratch[0][1] = &s->dither_scratch_base[0][1][1];
        s->dither_scratch[1][0] = &s->dither_scratch_base[1][0][1];
        s->dither_scratch[1][1] = &s->dither_scratch_base[1][1][1];
        s->dither_scratch[2][0] = &s->dither_scratch_base[2][0][1];
        s->dither_scratch[2][1] = &s->dither_scratch_base[2][1][1];
        if (!s->rgb[0] || !s->rgb[1] || !s->rgb[2] ||
            !s->dither_scratch_base[0][0] || !s->dither_scratch_base[0][1] ||
            !s->dither_scratch_base[1][0] || !s->dither_scratch_base[1][1] ||
            !s->dither_scratch_base[2][0] || !s->dither_scratch_base[2][1]) {
            uninit(ctx);
            return AVERROR(ENOMEM);
        }
        s->rgb_sz = rgb_sz;
    }
    res = create_filtergraph(ctx, in, out);
    if (res < 0)
        return res;
    s->rgb_stride = rgb_stride / sizeof(int16_t);
    td.in = in;
    td.out = out;
    td.in_linesize[0] = in->linesize[0];
    td.in_linesize[1] = in->linesize[1];
    td.in_linesize[2] = in->linesize[2];
    td.out_linesize[0] = out->linesize[0];
    td.out_linesize[1] = out->linesize[1];
    td.out_linesize[2] = out->linesize[2];
    td.in_ss_h = av_pix_fmt_desc_get(in->format)->log2_chroma_h;
    td.out_ss_h = av_pix_fmt_desc_get(out->format)->log2_chroma_h;
    if (s->yuv2yuv_passthrough) {
        res = av_frame_copy(out, in);
        if (res < 0)
            return res;
    } else {
        ctx->internal->execute(ctx, convert, &td, NULL,
                               FFMIN((in->height + 1) >> 1, ff_filter_get_nb_threads(ctx)));
    }
    av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}