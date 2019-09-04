#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_9__ ;
typedef  struct TYPE_50__   TYPE_8__ ;
typedef  struct TYPE_49__   TYPE_7__ ;
typedef  struct TYPE_48__   TYPE_6__ ;
typedef  struct TYPE_47__   TYPE_5__ ;
typedef  struct TYPE_46__   TYPE_4__ ;
typedef  struct TYPE_45__   TYPE_3__ ;
typedef  struct TYPE_44__   TYPE_2__ ;
typedef  struct TYPE_43__   TYPE_1__ ;
typedef  struct TYPE_42__   TYPE_19__ ;
typedef  struct TYPE_41__   TYPE_13__ ;
typedef  struct TYPE_40__   TYPE_12__ ;
typedef  struct TYPE_39__   TYPE_11__ ;
typedef  struct TYPE_38__   TYPE_10__ ;

/* Type definitions */
struct TYPE_48__ {TYPE_3__* plane; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ zimg_image_buffer_const ;
struct TYPE_49__ {TYPE_4__* plane; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_7__ zimg_image_buffer ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_40__ {int width; int height; int depth; scalar_t__ transfer_characteristics; scalar_t__ pixel_range; scalar_t__ color_primaries; scalar_t__ matrix_coefficients; void* color_family; void* pixel_type; scalar_t__ chroma_location; } ;
struct TYPE_41__ {int /*<<< orphan*/  resample_filter; void* cpu_type; int /*<<< orphan*/  dither_type; int /*<<< orphan*/  allow_approximate_gamma; int /*<<< orphan*/  nominal_peak_luminance; int /*<<< orphan*/  resample_filter_uv; } ;
struct TYPE_50__ {scalar_t__ in_colorspace; scalar_t__ in_trc; scalar_t__ in_primaries; scalar_t__ in_range; scalar_t__ out_colorspace; scalar_t__ out_trc; scalar_t__ out_primaries; scalar_t__ out_range; scalar_t__ in_chromal; scalar_t__ out_chromal; int colorspace_in; int primaries_in; int trc_in; int range_in; int chromal_in; int colorspace; int primaries; int trc; int range; int chromal; int /*<<< orphan*/  tmp; int /*<<< orphan*/  alpha_graph; int /*<<< orphan*/  graph; TYPE_12__ dst_format; TYPE_13__ alpha_params; TYPE_12__ alpha_dst_format; TYPE_12__ alpha_src_format; int /*<<< orphan*/  filter; int /*<<< orphan*/  dither; int /*<<< orphan*/  tmp_size; TYPE_12__ src_format; TYPE_13__ params; int /*<<< orphan*/  approximate_gamma; int /*<<< orphan*/  nominal_peak_luminance; } ;
typedef  TYPE_8__ ZScaleContext ;
struct TYPE_51__ {int flags; TYPE_5__* comp; } ;
struct TYPE_47__ {int depth; int plane; int step; } ;
struct TYPE_46__ {int stride; int mask; scalar_t__ data; } ;
struct TYPE_45__ {int stride; int mask; scalar_t__ data; } ;
struct TYPE_44__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_43__ {scalar_t__ format; int w; int h; } ;
struct TYPE_42__ {TYPE_1__** inputs; TYPE_11__** outputs; TYPE_8__* priv; } ;
struct TYPE_39__ {scalar_t__ format; int w; int h; TYPE_19__* dst; } ;
struct TYPE_38__ {int width; int height; scalar_t__ format; scalar_t__ colorspace; scalar_t__ color_trc; scalar_t__ color_primaries; scalar_t__ color_range; scalar_t__ chroma_location; int* linesize; scalar_t__* data; TYPE_2__ sample_aspect_ratio; } ;
typedef  TYPE_9__ AVPixFmtDescriptor ;
typedef  TYPE_10__ AVFrame ;
typedef  TYPE_11__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_PIX_FMT_FLAG_ALPHA ; 
 int AV_PIX_FMT_FLAG_FLOAT ; 
 int /*<<< orphan*/  AV_WN32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  ZIMG_API_VERSION ; 
 void* ZIMG_COLOR_GREY ; 
 void* ZIMG_CPU_AUTO ; 
 void* ZIMG_PIXEL_BYTE ; 
 void* ZIMG_PIXEL_FLOAT ; 
 void* ZIMG_PIXEL_WORD ; 
 int /*<<< orphan*/  av_float2int (float) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_10__*,TYPE_10__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_10__**) ; 
 int /*<<< orphan*/  av_opt_set (TYPE_8__*,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_9__* av_pix_fmt_desc_get (scalar_t__) ; 
 int /*<<< orphan*/  av_reduce (scalar_t__*,scalar_t__*,int,int,int /*<<< orphan*/ ) ; 
 int config_props (TYPE_11__*) ; 
 int ff_filter_frame (TYPE_11__*,TYPE_10__*) ; 
 TYPE_10__* ff_get_video_buffer (TYPE_11__*,int,int) ; 
 int /*<<< orphan*/  format_init (TYPE_12__*,TYPE_10__*,TYPE_9__ const*,int,int,int,int,int) ; 
 int graph_build (int /*<<< orphan*/ *,TYPE_13__*,TYPE_12__*,TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int print_zimg_error (TYPE_19__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  zimg_filter_graph_build (TYPE_12__*,TYPE_12__*,TYPE_13__*) ; 
 int /*<<< orphan*/  zimg_filter_graph_free (int /*<<< orphan*/ ) ; 
 int zimg_filter_graph_process (int /*<<< orphan*/ ,TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zimg_graph_builder_params_default (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zimg_image_format_default (TYPE_12__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *link, AVFrame *in)
{
    ZScaleContext *s = link->dst->priv;
    AVFilterLink *outlink = link->dst->outputs[0];
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(link->format);
    const AVPixFmtDescriptor *odesc = av_pix_fmt_desc_get(outlink->format);
    zimg_image_buffer_const src_buf = { ZIMG_API_VERSION };
    zimg_image_buffer dst_buf = { ZIMG_API_VERSION };
    char buf[32];
    int ret = 0, plane;
    AVFrame *out;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }

    av_frame_copy_props(out, in);
    out->width  = outlink->w;
    out->height = outlink->h;

    if(   in->width  != link->w
       || in->height != link->h
       || in->format != link->format
       || s->in_colorspace != in->colorspace
       || s->in_trc  != in->color_trc
       || s->in_primaries != in->color_primaries
       || s->in_range != in->color_range
       || s->out_colorspace != out->colorspace
       || s->out_trc  != out->color_trc
       || s->out_primaries != out->color_primaries
       || s->out_range != out->color_range
       || s->in_chromal != in->chroma_location
       || s->out_chromal != out->chroma_location) {
        snprintf(buf, sizeof(buf)-1, "%d", outlink->w);
        av_opt_set(s, "w", buf, 0);
        snprintf(buf, sizeof(buf)-1, "%d", outlink->h);
        av_opt_set(s, "h", buf, 0);

        link->dst->inputs[0]->format = in->format;
        link->dst->inputs[0]->w      = in->width;
        link->dst->inputs[0]->h      = in->height;

        if ((ret = config_props(outlink)) < 0) {
            av_frame_free(&in);
            av_frame_free(&out);
            return ret;
        }

        zimg_image_format_default(&s->src_format, ZIMG_API_VERSION);
        zimg_image_format_default(&s->dst_format, ZIMG_API_VERSION);
        zimg_graph_builder_params_default(&s->params, ZIMG_API_VERSION);

        s->params.dither_type = s->dither;
        s->params.cpu_type = ZIMG_CPU_AUTO;
        s->params.resample_filter = s->filter;
        s->params.resample_filter_uv = s->filter;
        s->params.nominal_peak_luminance = s->nominal_peak_luminance;
        s->params.allow_approximate_gamma = s->approximate_gamma;

        format_init(&s->src_format, in, desc, s->colorspace_in,
                    s->primaries_in, s->trc_in, s->range_in, s->chromal_in);
        format_init(&s->dst_format, out, odesc, s->colorspace,
                    s->primaries, s->trc, s->range, s->chromal);

        if (s->colorspace != -1)
            out->colorspace = (int)s->dst_format.matrix_coefficients;

        if (s->primaries != -1)
            out->color_primaries = (int)s->dst_format.color_primaries;

        if (s->range != -1)
            out->color_range = (int)s->dst_format.pixel_range + 1;

        if (s->trc != -1)
            out->color_trc = (int)s->dst_format.transfer_characteristics;

        if (s->chromal != -1)
            out->chroma_location = (int)s->dst_format.chroma_location - 1;

        ret = graph_build(&s->graph, &s->params, &s->src_format, &s->dst_format,
                          &s->tmp, &s->tmp_size);
        if (ret < 0)
            goto fail;

        s->in_colorspace  = in->colorspace;
        s->in_trc         = in->color_trc;
        s->in_primaries   = in->color_primaries;
        s->in_range       = in->color_range;
        s->out_colorspace = out->colorspace;
        s->out_trc        = out->color_trc;
        s->out_primaries  = out->color_primaries;
        s->out_range      = out->color_range;

        if (desc->flags & AV_PIX_FMT_FLAG_ALPHA && odesc->flags & AV_PIX_FMT_FLAG_ALPHA) {
            zimg_image_format_default(&s->alpha_src_format, ZIMG_API_VERSION);
            zimg_image_format_default(&s->alpha_dst_format, ZIMG_API_VERSION);
            zimg_graph_builder_params_default(&s->alpha_params, ZIMG_API_VERSION);

            s->alpha_params.dither_type = s->dither;
            s->alpha_params.cpu_type = ZIMG_CPU_AUTO;
            s->alpha_params.resample_filter = s->filter;

            s->alpha_src_format.width = in->width;
            s->alpha_src_format.height = in->height;
            s->alpha_src_format.depth = desc->comp[0].depth;
            s->alpha_src_format.pixel_type = (desc->flags & AV_PIX_FMT_FLAG_FLOAT) ? ZIMG_PIXEL_FLOAT : desc->comp[0].depth > 8 ? ZIMG_PIXEL_WORD : ZIMG_PIXEL_BYTE;
            s->alpha_src_format.color_family = ZIMG_COLOR_GREY;

            s->alpha_dst_format.width = out->width;
            s->alpha_dst_format.height = out->height;
            s->alpha_dst_format.depth = odesc->comp[0].depth;
            s->alpha_dst_format.pixel_type = (odesc->flags & AV_PIX_FMT_FLAG_FLOAT) ? ZIMG_PIXEL_FLOAT : odesc->comp[0].depth > 8 ? ZIMG_PIXEL_WORD : ZIMG_PIXEL_BYTE;
            s->alpha_dst_format.color_family = ZIMG_COLOR_GREY;

            zimg_filter_graph_free(s->alpha_graph);
            s->alpha_graph = zimg_filter_graph_build(&s->alpha_src_format, &s->alpha_dst_format, &s->alpha_params);
            if (!s->alpha_graph) {
                ret = print_zimg_error(link->dst);
                goto fail;
            }
        }
    }

    if (s->colorspace != -1)
        out->colorspace = (int)s->dst_format.matrix_coefficients;

    if (s->primaries != -1)
        out->color_primaries = (int)s->dst_format.color_primaries;

    if (s->range != -1)
        out->color_range = (int)s->dst_format.pixel_range;

    if (s->trc != -1)
        out->color_trc = (int)s->dst_format.transfer_characteristics;

    av_reduce(&out->sample_aspect_ratio.num, &out->sample_aspect_ratio.den,
              (int64_t)in->sample_aspect_ratio.num * outlink->h * link->w,
              (int64_t)in->sample_aspect_ratio.den * outlink->w * link->h,
              INT_MAX);

    for (plane = 0; plane < 3; plane++) {
        int p = desc->comp[plane].plane;
        src_buf.plane[plane].data   = in->data[p];
        src_buf.plane[plane].stride = in->linesize[p];
        src_buf.plane[plane].mask   = -1;

        p = odesc->comp[plane].plane;
        dst_buf.plane[plane].data   = out->data[p];
        dst_buf.plane[plane].stride = out->linesize[p];
        dst_buf.plane[plane].mask   = -1;
    }

    ret = zimg_filter_graph_process(s->graph, &src_buf, &dst_buf, s->tmp, 0, 0, 0, 0);
    if (ret) {
        ret = print_zimg_error(link->dst);
        goto fail;
    }

    if (desc->flags & AV_PIX_FMT_FLAG_ALPHA && odesc->flags & AV_PIX_FMT_FLAG_ALPHA) {
        src_buf.plane[0].data   = in->data[3];
        src_buf.plane[0].stride = in->linesize[3];
        src_buf.plane[0].mask   = -1;

        dst_buf.plane[0].data   = out->data[3];
        dst_buf.plane[0].stride = out->linesize[3];
        dst_buf.plane[0].mask   = -1;

        ret = zimg_filter_graph_process(s->alpha_graph, &src_buf, &dst_buf, s->tmp, 0, 0, 0, 0);
        if (ret) {
            ret = print_zimg_error(link->dst);
            goto fail;
        }
    } else if (odesc->flags & AV_PIX_FMT_FLAG_ALPHA) {
        int x, y;

        if (odesc->flags & AV_PIX_FMT_FLAG_FLOAT) {
            for (y = 0; y < out->height; y++) {
                for (x = 0; x < out->width; x++) {
                    AV_WN32(out->data[3] + x * odesc->comp[3].step + y * out->linesize[3],
                            av_float2int(1.0f));
                }
            }
        } else {
            for (y = 0; y < outlink->h; y++)
                memset(out->data[3] + y * out->linesize[3], 0xff, outlink->w);
        }
    }

fail:
    av_frame_free(&in);
    if (ret) {
        av_frame_free(&out);
        return ret;
    }

    return ff_filter_frame(outlink, out);
}