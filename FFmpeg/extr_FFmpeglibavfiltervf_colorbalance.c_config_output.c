#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_5__* priv; } ;
struct TYPE_18__ {int /*<<< orphan*/  format; TYPE_8__* src; } ;
struct TYPE_17__ {TYPE_1__* comp; } ;
struct TYPE_15__ {double shadows; double midtones; double highlights; } ;
struct TYPE_14__ {double shadows; double midtones; double highlights; } ;
struct TYPE_13__ {double shadows; double midtones; double highlights; } ;
struct TYPE_16__ {int** lut; int step; int /*<<< orphan*/  rgba_map; TYPE_4__ yellow_blue; TYPE_3__ magenta_green; TYPE_2__ cyan_red; int /*<<< orphan*/  apply_lut; } ;
struct TYPE_12__ {int depth; } ;
typedef  TYPE_5__ ColorBalanceContext ;
typedef  TYPE_6__ AVPixFmtDescriptor ;
typedef  TYPE_7__ AVFilterLink ;
typedef  TYPE_8__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 size_t B ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t G ; 
 size_t R ; 
 int /*<<< orphan*/  apply_lut16 ; 
 int /*<<< orphan*/  apply_lut16_p ; 
 int /*<<< orphan*/  apply_lut8 ; 
 int /*<<< orphan*/  apply_lut8_p ; 
 int av_clip_uintp2_c (int,int const) ; 
 double const av_clipd (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_free (double*) ; 
 int av_get_padded_bits_per_pixel (TYPE_6__ const*) ; 
 double* av_malloc (int const) ; 
 int av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_6__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_fill_rgba_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    ColorBalanceContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(outlink->format);
    const int depth = desc->comp[0].depth;
    const int max = 1 << depth;
    const int planar = av_pix_fmt_count_planes(outlink->format) > 1;
    double *shadows, *midtones, *highlights, *buffer;
    int i, r, g, b;

    if (max == 256 && planar) {
        s->apply_lut = apply_lut8_p;
    } else if (planar) {
        s->apply_lut = apply_lut16_p;
    } else if (max == 256) {
        s->apply_lut = apply_lut8;
    } else {
        s->apply_lut = apply_lut16;
    }

    buffer = av_malloc(max * 3 * sizeof(*buffer));
    if (!buffer)
        return AVERROR(ENOMEM);

    shadows    = buffer + max * 0;
    midtones   = buffer + max * 1;
    highlights = buffer + max * 2;

    for (i = 0; i < max; i++) {
        const double L = 0.333 * (max - 1);
        const double M = 0.7 * (max - 1);
        const double H = 1 * (max - 1);
        double low = av_clipd((i - L) / (-max * 0.25) + 0.5, 0, 1) * M;
        double mid = av_clipd((i - L) / ( max * 0.25) + 0.5, 0, 1) *
                     av_clipd((i + L - H) / (-max * 0.25) + 0.5, 0, 1) * M;

        shadows[i] = low;
        midtones[i] = mid;
        highlights[max - i - 1] = low;
    }

    for (i = 0; i < max; i++) {
        r = g = b = i;

        r = av_clip_uintp2_c(r + s->cyan_red.shadows         * shadows[r],    depth);
        r = av_clip_uintp2_c(r + s->cyan_red.midtones        * midtones[r],   depth);
        r = av_clip_uintp2_c(r + s->cyan_red.highlights      * highlights[r], depth);

        g = av_clip_uintp2_c(g + s->magenta_green.shadows    * shadows[g],    depth);
        g = av_clip_uintp2_c(g + s->magenta_green.midtones   * midtones[g],   depth);
        g = av_clip_uintp2_c(g + s->magenta_green.highlights * highlights[g], depth);

        b = av_clip_uintp2_c(b + s->yellow_blue.shadows      * shadows[b],    depth);
        b = av_clip_uintp2_c(b + s->yellow_blue.midtones     * midtones[b],   depth);
        b = av_clip_uintp2_c(b + s->yellow_blue.highlights   * highlights[b], depth);

        s->lut[R][i] = r;
        s->lut[G][i] = g;
        s->lut[B][i] = b;
    }

    av_free(buffer);

    ff_fill_rgba_map(s->rgba_map, outlink->format);
    s->step = av_get_padded_bits_per_pixel(desc) >> 3;

    return 0;
}