#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_20__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_27__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_32__ {scalar_t__ format; int w; int h; TYPE_20__* dst; TYPE_3__ sample_aspect_ratio; } ;
struct TYPE_26__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_31__ {int width; int height; scalar_t__ format; int color_range; scalar_t__ interlaced_frame; TYPE_2__ sample_aspect_ratio; int /*<<< orphan*/  colorspace; scalar_t__* data; } ;
struct TYPE_30__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
struct TYPE_29__ {scalar_t__ eval_mode; int in_range; int out_range; scalar_t__ interlaced; int nb_slices; scalar_t__ sws; scalar_t__* isws; scalar_t__ in_color_matrix; scalar_t__ out_color_matrix; scalar_t__ output_is_pal; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; } ;
struct TYPE_24__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_28__ {scalar_t__ format; int w; int h; TYPE_1__ sample_aspect_ratio; } ;
struct TYPE_25__ {TYPE_4__** inputs; TYPE_8__** outputs; TYPE_5__* priv; } ;
typedef  TYPE_5__ ScaleContext ;
typedef  TYPE_6__ AVPixFmtDescriptor ;
typedef  TYPE_7__ AVFrame ;
typedef  TYPE_8__ AVFilterLink ;

/* Variables and functions */
 int AVCOL_RANGE_JPEG ; 
 int AVCOL_RANGE_MPEG ; 
 int AVCOL_RANGE_UNSPECIFIED ; 
 int /*<<< orphan*/  AVCOL_SPC_UNSPECIFIED ; 
 int /*<<< orphan*/  AVCOL_SPC_YCGCO ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PIX_FMT_BGR8 ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ EVAL_MODE_INIT ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_7__**) ; 
 int /*<<< orphan*/  av_log (TYPE_20__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_opt_set (TYPE_5__*,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_6__* av_pix_fmt_desc_get (scalar_t__) ; 
 int /*<<< orphan*/  av_reduce (scalar_t__*,scalar_t__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_systematic_pal2 (int /*<<< orphan*/ *,scalar_t__) ; 
 int config_props (TYPE_8__*) ; 
 TYPE_7__* ff_get_video_buffer (TYPE_8__*,int,int) ; 
 int* parse_yuv_type (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scale_slice (TYPE_8__*,TYPE_7__*,TYPE_7__*,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sws_getColorspaceDetails (scalar_t__,int**,int*,int**,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  sws_setColorspaceDetails (scalar_t__,int const*,int,int const*,int,int,int,int) ; 

__attribute__((used)) static int scale_frame(AVFilterLink *link, AVFrame *in, AVFrame **frame_out)
{
    ScaleContext *scale = link->dst->priv;
    AVFilterLink *outlink = link->dst->outputs[0];
    AVFrame *out;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(link->format);
    char buf[32];
    int in_range;

    *frame_out = NULL;
    if (in->colorspace == AVCOL_SPC_YCGCO)
        av_log(link->dst, AV_LOG_WARNING, "Detected unsupported YCgCo colorspace.\n");

    if (  in->width  != link->w
       || in->height != link->h
       || in->format != link->format
       || in->sample_aspect_ratio.den != link->sample_aspect_ratio.den || in->sample_aspect_ratio.num != link->sample_aspect_ratio.num) {
        int ret;

        if (scale->eval_mode == EVAL_MODE_INIT) {
            snprintf(buf, sizeof(buf)-1, "%d", outlink->w);
            av_opt_set(scale, "w", buf, 0);
            snprintf(buf, sizeof(buf)-1, "%d", outlink->h);
            av_opt_set(scale, "h", buf, 0);
        }

        link->dst->inputs[0]->format = in->format;
        link->dst->inputs[0]->w      = in->width;
        link->dst->inputs[0]->h      = in->height;

        link->dst->inputs[0]->sample_aspect_ratio.den = in->sample_aspect_ratio.den;
        link->dst->inputs[0]->sample_aspect_ratio.num = in->sample_aspect_ratio.num;

        if ((ret = config_props(outlink)) < 0)
            return ret;
    }

    if (!scale->sws) {
        *frame_out = in;
        return 0;
    }

    scale->hsub = desc->log2_chroma_w;
    scale->vsub = desc->log2_chroma_h;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    *frame_out = out;

    av_frame_copy_props(out, in);
    out->width  = outlink->w;
    out->height = outlink->h;

    if (scale->output_is_pal)
        avpriv_set_systematic_pal2((uint32_t*)out->data[1], outlink->format == AV_PIX_FMT_PAL8 ? AV_PIX_FMT_BGR8 : outlink->format);

    in_range = in->color_range;

    if (   scale->in_color_matrix
        || scale->out_color_matrix
        || scale-> in_range != AVCOL_RANGE_UNSPECIFIED
        || in_range != AVCOL_RANGE_UNSPECIFIED
        || scale->out_range != AVCOL_RANGE_UNSPECIFIED) {
        int in_full, out_full, brightness, contrast, saturation;
        const int *inv_table, *table;

        sws_getColorspaceDetails(scale->sws, (int **)&inv_table, &in_full,
                                 (int **)&table, &out_full,
                                 &brightness, &contrast, &saturation);

        if (scale->in_color_matrix)
            inv_table = parse_yuv_type(scale->in_color_matrix, in->colorspace);
        if (scale->out_color_matrix)
            table     = parse_yuv_type(scale->out_color_matrix, AVCOL_SPC_UNSPECIFIED);
        else if (scale->in_color_matrix)
            table = inv_table;

        if (scale-> in_range != AVCOL_RANGE_UNSPECIFIED)
            in_full  = (scale-> in_range == AVCOL_RANGE_JPEG);
        else if (in_range != AVCOL_RANGE_UNSPECIFIED)
            in_full  = (in_range == AVCOL_RANGE_JPEG);
        if (scale->out_range != AVCOL_RANGE_UNSPECIFIED)
            out_full = (scale->out_range == AVCOL_RANGE_JPEG);

        sws_setColorspaceDetails(scale->sws, inv_table, in_full,
                                 table, out_full,
                                 brightness, contrast, saturation);
        if (scale->isws[0])
            sws_setColorspaceDetails(scale->isws[0], inv_table, in_full,
                                     table, out_full,
                                     brightness, contrast, saturation);
        if (scale->isws[1])
            sws_setColorspaceDetails(scale->isws[1], inv_table, in_full,
                                     table, out_full,
                                     brightness, contrast, saturation);

        out->color_range = out_full ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG;
    }

    av_reduce(&out->sample_aspect_ratio.num, &out->sample_aspect_ratio.den,
              (int64_t)in->sample_aspect_ratio.num * outlink->h * link->w,
              (int64_t)in->sample_aspect_ratio.den * outlink->w * link->h,
              INT_MAX);

    if (scale->interlaced>0 || (scale->interlaced<0 && in->interlaced_frame)) {
        scale_slice(link, out, in, scale->isws[0], 0, (link->h+1)/2, 2, 0);
        scale_slice(link, out, in, scale->isws[1], 0,  link->h   /2, 2, 1);
    } else if (scale->nb_slices) {
        int i, slice_h, slice_start, slice_end = 0;
        const int nb_slices = FFMIN(scale->nb_slices, link->h);
        for (i = 0; i < nb_slices; i++) {
            slice_start = slice_end;
            slice_end   = (link->h * (i+1)) / nb_slices;
            slice_h     = slice_end - slice_start;
            scale_slice(link, out, in, scale->sws, slice_start, slice_h, 1, 0);
        }
    } else {
        scale_slice(link, out, in, scale->sws, 0, link->h, 1, 0);
    }

    av_frame_free(&in);
    return 0;
}