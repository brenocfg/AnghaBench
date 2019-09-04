#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct WhitepointCoefficients {int dummy; } ;
struct TYPE_23__ {size_t wp; int /*<<< orphan*/  coeff; } ;
struct TYPE_22__ {TYPE_3__* priv; } ;
struct TYPE_21__ {scalar_t__ color_primaries; scalar_t__ color_trc; scalar_t__ colorspace; scalar_t__ color_range; int /*<<< orphan*/  format; } ;
struct TYPE_20__ {int nb_components; int flags; int log2_chroma_w; int log2_chroma_h; TYPE_1__* comp; } ;
struct TYPE_18__ {int /*<<< orphan*/ *** yuv2yuv; int /*<<< orphan*/ ** rgb2yuv_fsb; int /*<<< orphan*/ ** rgb2yuv; int /*<<< orphan*/ ** yuv2rgb; } ;
struct TYPE_19__ {scalar_t__ in_prm; scalar_t__ out_prm; scalar_t__ in_trc; scalar_t__ out_trc; scalar_t__ in_csp; scalar_t__ in_rng; scalar_t__ out_csp; scalar_t__ out_rng; scalar_t__ user_iall; scalar_t__ user_iprm; scalar_t__ user_all; int lrgb2lrgb_passthrough; scalar_t__ wp_adapt; scalar_t__ user_itrc; int rgb2rgb_passthrough; scalar_t__ user_icsp; scalar_t__ user_irng; int yuv2yuv_fastmode; int yuv2yuv_passthrough; double** yuv2rgb_dbl_coeffs; int in_y_rng; int in_uv_rng; int** yuv_offset; double** rgb2yuv_dbl_coeffs; int out_y_rng; int out_uv_rng; TYPE_2__ dsp; int /*<<< orphan*/  yuv2yuv; void**** yuv2yuv_coeffs; int /*<<< orphan*/  rgb2yuv_fsb; int /*<<< orphan*/  rgb2yuv; void**** rgb2yuv_coeffs; TYPE_7__* out_lumacoef; int /*<<< orphan*/  yuv2rgb; void**** yuv2rgb_coeffs; TYPE_7__* in_lumacoef; int /*<<< orphan*/  lin_lut; TYPE_7__* out_txchr; TYPE_7__* in_txchr; scalar_t__ fast_mode; void**** lrgb2lrgb_coeffs; TYPE_7__* out_primaries; TYPE_7__* in_primaries; } ;
struct TYPE_17__ {int depth; } ;
typedef  TYPE_3__ ColorSpaceContext ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AVCOL_PRI_UNSPECIFIED ; 
 scalar_t__ AVCOL_RANGE_UNSPECIFIED ; 
 scalar_t__ AVCOL_SPC_UNSPECIFIED ; 
 scalar_t__ AVCOL_TRC_UNSPECIFIED ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_FLAG_RGB ; 
 int /*<<< orphan*/  CS_NB ; 
 scalar_t__ CS_UNSPECIFIED ; 
 int /*<<< orphan*/  EINVAL ; 
 size_t FFMIN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ WP_ADAPT_IDENTITY ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  av_color_primaries_name (scalar_t__) ; 
 int /*<<< orphan*/  av_color_range_name (scalar_t__) ; 
 int /*<<< orphan*/  av_color_space_name (scalar_t__) ; 
 int /*<<< orphan*/  av_color_transfer_name (scalar_t__) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 scalar_t__* default_csp ; 
 scalar_t__* default_prm ; 
 scalar_t__* default_trc ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  ff_fill_rgb2xyz_table (int /*<<< orphan*/ *,struct WhitepointCoefficients const*,double**) ; 
 int /*<<< orphan*/  ff_fill_rgb2yuv_table (TYPE_7__*,double**) ; 
 void* ff_get_luma_coefficients (scalar_t__) ; 
 int /*<<< orphan*/  ff_matrix_invert_3x3 (double**,double**) ; 
 int /*<<< orphan*/  ff_matrix_mul_3x3 (double**,double**,double**) ; 
 int fill_gamma_table (TYPE_3__*) ; 
 int /*<<< orphan*/  fill_whitepoint_conv_table (double**,scalar_t__,size_t,size_t) ; 
 void* get_color_primaries (scalar_t__) ; 
 int get_range_off (TYPE_6__*,int*,int*,int*,scalar_t__,int) ; 
 void* get_transfer_characteristics (scalar_t__) ; 
 void* lrint (int) ; 
 int /*<<< orphan*/  memcmp (TYPE_7__*,TYPE_7__*,int) ; 
 struct WhitepointCoefficients* whitepoint_coefficients ; 

__attribute__((used)) static int create_filtergraph(AVFilterContext *ctx,
                              const AVFrame *in, const AVFrame *out)
{
    ColorSpaceContext *s = ctx->priv;
    const AVPixFmtDescriptor *in_desc  = av_pix_fmt_desc_get(in->format);
    const AVPixFmtDescriptor *out_desc = av_pix_fmt_desc_get(out->format);
    int emms = 0, m, n, o, res, fmt_identical, redo_yuv2rgb = 0, redo_rgb2yuv = 0;

#define supported_depth(d) ((d) == 8 || (d) == 10 || (d) == 12)
#define supported_subsampling(lcw, lch) \
    (((lcw) == 0 && (lch) == 0) || ((lcw) == 1 && (lch) == 0) || ((lcw) == 1 && (lch) == 1))
#define supported_format(d) \
    ((d) != NULL && (d)->nb_components == 3 && \
     !((d)->flags & AV_PIX_FMT_FLAG_RGB) && \
     supported_depth((d)->comp[0].depth) && \
     supported_subsampling((d)->log2_chroma_w, (d)->log2_chroma_h))

    if (!supported_format(in_desc)) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported input format %d (%s) or bitdepth (%d)\n",
               in->format, av_get_pix_fmt_name(in->format),
               in_desc ? in_desc->comp[0].depth : -1);
        return AVERROR(EINVAL);
    }
    if (!supported_format(out_desc)) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported output format %d (%s) or bitdepth (%d)\n",
               out->format, av_get_pix_fmt_name(out->format),
               out_desc ? out_desc->comp[0].depth : -1);
        return AVERROR(EINVAL);
    }

    if (in->color_primaries  != s->in_prm)  s->in_primaries  = NULL;
    if (out->color_primaries != s->out_prm) s->out_primaries = NULL;
    if (in->color_trc        != s->in_trc)  s->in_txchr      = NULL;
    if (out->color_trc       != s->out_trc) s->out_txchr     = NULL;
    if (in->colorspace       != s->in_csp ||
        in->color_range      != s->in_rng)  s->in_lumacoef   = NULL;
    if (out->colorspace      != s->out_csp ||
        out->color_range     != s->out_rng) s->out_lumacoef  = NULL;

    if (!s->out_primaries || !s->in_primaries) {
        s->in_prm = in->color_primaries;
        if (s->user_iall != CS_UNSPECIFIED)
            s->in_prm = default_prm[FFMIN(s->user_iall, CS_NB)];
        if (s->user_iprm != AVCOL_PRI_UNSPECIFIED)
            s->in_prm = s->user_iprm;
        s->in_primaries = get_color_primaries(s->in_prm);
        if (!s->in_primaries) {
            av_log(ctx, AV_LOG_ERROR,
                   "Unsupported input primaries %d (%s)\n",
                   s->in_prm, av_color_primaries_name(s->in_prm));
            return AVERROR(EINVAL);
        }
        s->out_prm = out->color_primaries;
        s->out_primaries = get_color_primaries(s->out_prm);
        if (!s->out_primaries) {
            if (s->out_prm == AVCOL_PRI_UNSPECIFIED) {
                if (s->user_all == CS_UNSPECIFIED) {
                    av_log(ctx, AV_LOG_ERROR, "Please specify output primaries\n");
                } else {
                    av_log(ctx, AV_LOG_ERROR,
                           "Unsupported output color property %d\n", s->user_all);
                }
            } else {
                av_log(ctx, AV_LOG_ERROR,
                       "Unsupported output primaries %d (%s)\n",
                       s->out_prm, av_color_primaries_name(s->out_prm));
            }
            return AVERROR(EINVAL);
        }
        s->lrgb2lrgb_passthrough = !memcmp(s->in_primaries, s->out_primaries,
                                           sizeof(*s->in_primaries));
        if (!s->lrgb2lrgb_passthrough) {
            double rgb2xyz[3][3], xyz2rgb[3][3], rgb2rgb[3][3];
            const struct WhitepointCoefficients *wp_out, *wp_in;

            wp_out = &whitepoint_coefficients[s->out_primaries->wp];
            wp_in = &whitepoint_coefficients[s->in_primaries->wp];
            ff_fill_rgb2xyz_table(&s->out_primaries->coeff, wp_out, rgb2xyz);
            ff_matrix_invert_3x3(rgb2xyz, xyz2rgb);
            ff_fill_rgb2xyz_table(&s->in_primaries->coeff, wp_in, rgb2xyz);
            if (s->out_primaries->wp != s->in_primaries->wp &&
                s->wp_adapt != WP_ADAPT_IDENTITY) {
                double wpconv[3][3], tmp[3][3];

                fill_whitepoint_conv_table(wpconv, s->wp_adapt, s->in_primaries->wp,
                                           s->out_primaries->wp);
                ff_matrix_mul_3x3(tmp, rgb2xyz, wpconv);
                ff_matrix_mul_3x3(rgb2rgb, tmp, xyz2rgb);
            } else {
                ff_matrix_mul_3x3(rgb2rgb, rgb2xyz, xyz2rgb);
            }
            for (m = 0; m < 3; m++)
                for (n = 0; n < 3; n++) {
                    s->lrgb2lrgb_coeffs[m][n][0] = lrint(16384.0 * rgb2rgb[m][n]);
                    for (o = 1; o < 8; o++)
                        s->lrgb2lrgb_coeffs[m][n][o] = s->lrgb2lrgb_coeffs[m][n][0];
                }

            emms = 1;
        }
    }

    if (!s->in_txchr) {
        av_freep(&s->lin_lut);
        s->in_trc = in->color_trc;
        if (s->user_iall != CS_UNSPECIFIED)
            s->in_trc = default_trc[FFMIN(s->user_iall, CS_NB)];
        if (s->user_itrc != AVCOL_TRC_UNSPECIFIED)
            s->in_trc = s->user_itrc;
        s->in_txchr = get_transfer_characteristics(s->in_trc);
        if (!s->in_txchr) {
            av_log(ctx, AV_LOG_ERROR,
                   "Unsupported input transfer characteristics %d (%s)\n",
                   s->in_trc, av_color_transfer_name(s->in_trc));
            return AVERROR(EINVAL);
        }
    }

    if (!s->out_txchr) {
        av_freep(&s->lin_lut);
        s->out_trc = out->color_trc;
        s->out_txchr = get_transfer_characteristics(s->out_trc);
        if (!s->out_txchr) {
            if (s->out_trc == AVCOL_TRC_UNSPECIFIED) {
                if (s->user_all == CS_UNSPECIFIED) {
                    av_log(ctx, AV_LOG_ERROR,
                           "Please specify output transfer characteristics\n");
                } else {
                    av_log(ctx, AV_LOG_ERROR,
                           "Unsupported output color property %d\n", s->user_all);
                }
            } else {
                av_log(ctx, AV_LOG_ERROR,
                       "Unsupported output transfer characteristics %d (%s)\n",
                       s->out_trc, av_color_transfer_name(s->out_trc));
            }
            return AVERROR(EINVAL);
        }
    }

    s->rgb2rgb_passthrough = s->fast_mode || (s->lrgb2lrgb_passthrough &&
                             !memcmp(s->in_txchr, s->out_txchr, sizeof(*s->in_txchr)));
    if (!s->rgb2rgb_passthrough && !s->lin_lut) {
        res = fill_gamma_table(s);
        if (res < 0)
            return res;
        emms = 1;
    }

    if (!s->in_lumacoef) {
        s->in_csp = in->colorspace;
        if (s->user_iall != CS_UNSPECIFIED)
            s->in_csp = default_csp[FFMIN(s->user_iall, CS_NB)];
        if (s->user_icsp != AVCOL_SPC_UNSPECIFIED)
            s->in_csp = s->user_icsp;
        s->in_rng = in->color_range;
        if (s->user_irng != AVCOL_RANGE_UNSPECIFIED)
            s->in_rng = s->user_irng;
        s->in_lumacoef = ff_get_luma_coefficients(s->in_csp);
        if (!s->in_lumacoef) {
            av_log(ctx, AV_LOG_ERROR,
                   "Unsupported input colorspace %d (%s)\n",
                   s->in_csp, av_color_space_name(s->in_csp));
            return AVERROR(EINVAL);
        }
        redo_yuv2rgb = 1;
    }

    if (!s->out_lumacoef) {
        s->out_csp = out->colorspace;
        s->out_rng = out->color_range;
        s->out_lumacoef = ff_get_luma_coefficients(s->out_csp);
        if (!s->out_lumacoef) {
            if (s->out_csp == AVCOL_SPC_UNSPECIFIED) {
                if (s->user_all == CS_UNSPECIFIED) {
                    av_log(ctx, AV_LOG_ERROR,
                           "Please specify output transfer characteristics\n");
                } else {
                    av_log(ctx, AV_LOG_ERROR,
                           "Unsupported output color property %d\n", s->user_all);
                }
            } else {
                av_log(ctx, AV_LOG_ERROR,
                       "Unsupported output transfer characteristics %d (%s)\n",
                       s->out_csp, av_color_space_name(s->out_csp));
            }
            return AVERROR(EINVAL);
        }
        redo_rgb2yuv = 1;
    }

    fmt_identical = in_desc->log2_chroma_h == out_desc->log2_chroma_h &&
                    in_desc->log2_chroma_w == out_desc->log2_chroma_w;
    s->yuv2yuv_fastmode = s->rgb2rgb_passthrough && fmt_identical;
    s->yuv2yuv_passthrough = s->yuv2yuv_fastmode && s->in_rng == s->out_rng &&
                             !memcmp(s->in_lumacoef, s->out_lumacoef,
                                     sizeof(*s->in_lumacoef)) &&
                             in_desc->comp[0].depth == out_desc->comp[0].depth;
    if (!s->yuv2yuv_passthrough) {
        if (redo_yuv2rgb) {
            double rgb2yuv[3][3], (*yuv2rgb)[3] = s->yuv2rgb_dbl_coeffs;
            int off, bits, in_rng;

            res = get_range_off(ctx, &off, &s->in_y_rng, &s->in_uv_rng,
                                s->in_rng, in_desc->comp[0].depth);
            if (res < 0) {
                av_log(ctx, AV_LOG_ERROR,
                       "Unsupported input color range %d (%s)\n",
                       s->in_rng, av_color_range_name(s->in_rng));
                return res;
            }
            for (n = 0; n < 8; n++)
                s->yuv_offset[0][n] = off;
            ff_fill_rgb2yuv_table(s->in_lumacoef, rgb2yuv);
            ff_matrix_invert_3x3(rgb2yuv, yuv2rgb);
            bits = 1 << (in_desc->comp[0].depth - 1);
            for (n = 0; n < 3; n++) {
                for (in_rng = s->in_y_rng, m = 0; m < 3; m++, in_rng = s->in_uv_rng) {
                    s->yuv2rgb_coeffs[n][m][0] = lrint(28672 * bits * yuv2rgb[n][m] / in_rng);
                    for (o = 1; o < 8; o++)
                        s->yuv2rgb_coeffs[n][m][o] = s->yuv2rgb_coeffs[n][m][0];
                }
            }
            av_assert2(s->yuv2rgb_coeffs[0][1][0] == 0);
            av_assert2(s->yuv2rgb_coeffs[2][2][0] == 0);
            av_assert2(s->yuv2rgb_coeffs[0][0][0] == s->yuv2rgb_coeffs[1][0][0]);
            av_assert2(s->yuv2rgb_coeffs[0][0][0] == s->yuv2rgb_coeffs[2][0][0]);
            s->yuv2rgb = s->dsp.yuv2rgb[(in_desc->comp[0].depth - 8) >> 1]
                                       [in_desc->log2_chroma_h + in_desc->log2_chroma_w];
            emms = 1;
        }

        if (redo_rgb2yuv) {
            double (*rgb2yuv)[3] = s->rgb2yuv_dbl_coeffs;
            int off, out_rng, bits;

            res = get_range_off(ctx, &off, &s->out_y_rng, &s->out_uv_rng,
                                s->out_rng, out_desc->comp[0].depth);
            if (res < 0) {
                av_log(ctx, AV_LOG_ERROR,
                       "Unsupported output color range %d (%s)\n",
                       s->out_rng, av_color_range_name(s->out_rng));
                return res;
            }
            for (n = 0; n < 8; n++)
                s->yuv_offset[1][n] = off;
            ff_fill_rgb2yuv_table(s->out_lumacoef, rgb2yuv);
            bits = 1 << (29 - out_desc->comp[0].depth);
            for (out_rng = s->out_y_rng, n = 0; n < 3; n++, out_rng = s->out_uv_rng) {
                for (m = 0; m < 3; m++) {
                    s->rgb2yuv_coeffs[n][m][0] = lrint(bits * out_rng * rgb2yuv[n][m] / 28672);
                    for (o = 1; o < 8; o++)
                        s->rgb2yuv_coeffs[n][m][o] = s->rgb2yuv_coeffs[n][m][0];
                }
            }
            av_assert2(s->rgb2yuv_coeffs[1][2][0] == s->rgb2yuv_coeffs[2][0][0]);
            s->rgb2yuv = s->dsp.rgb2yuv[(out_desc->comp[0].depth - 8) >> 1]
                                       [out_desc->log2_chroma_h + out_desc->log2_chroma_w];
            s->rgb2yuv_fsb = s->dsp.rgb2yuv_fsb[(out_desc->comp[0].depth - 8) >> 1]
                                       [out_desc->log2_chroma_h + out_desc->log2_chroma_w];
            emms = 1;
        }

        if (s->yuv2yuv_fastmode && (redo_yuv2rgb || redo_rgb2yuv)) {
            int idepth = in_desc->comp[0].depth, odepth = out_desc->comp[0].depth;
            double (*rgb2yuv)[3] = s->rgb2yuv_dbl_coeffs;
            double (*yuv2rgb)[3] = s->yuv2rgb_dbl_coeffs;
            double yuv2yuv[3][3];
            int in_rng, out_rng;

            ff_matrix_mul_3x3(yuv2yuv, yuv2rgb, rgb2yuv);
            for (out_rng = s->out_y_rng, m = 0; m < 3; m++, out_rng = s->out_uv_rng) {
                for (in_rng = s->in_y_rng, n = 0; n < 3; n++, in_rng = s->in_uv_rng) {
                    s->yuv2yuv_coeffs[m][n][0] =
                        lrint(16384 * yuv2yuv[m][n] * out_rng * (1 << idepth) /
                              (in_rng * (1 << odepth)));
                    for (o = 1; o < 8; o++)
                        s->yuv2yuv_coeffs[m][n][o] = s->yuv2yuv_coeffs[m][n][0];
                }
            }
            av_assert2(s->yuv2yuv_coeffs[1][0][0] == 0);
            av_assert2(s->yuv2yuv_coeffs[2][0][0] == 0);
            s->yuv2yuv = s->dsp.yuv2yuv[(idepth - 8) >> 1][(odepth - 8) >> 1]
                                       [in_desc->log2_chroma_h + in_desc->log2_chroma_w];
        }
    }

    if (emms)
        emms_c();

    return 0;
}