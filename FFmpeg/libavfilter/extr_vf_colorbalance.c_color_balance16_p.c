#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  float uint16_t ;
struct TYPE_12__ {TYPE_6__* out; TYPE_6__* in; } ;
typedef  TYPE_4__ ThreadData ;
struct TYPE_15__ {TYPE_5__* priv; } ;
struct TYPE_14__ {int height; int const* linesize; int width; scalar_t__* data; } ;
struct TYPE_11__ {int /*<<< orphan*/  highlights; int /*<<< orphan*/  midtones; int /*<<< orphan*/  shadows; } ;
struct TYPE_10__ {int /*<<< orphan*/  highlights; int /*<<< orphan*/  midtones; int /*<<< orphan*/  shadows; } ;
struct TYPE_9__ {int /*<<< orphan*/  highlights; int /*<<< orphan*/  midtones; int /*<<< orphan*/  shadows; } ;
struct TYPE_13__ {int depth; float max; scalar_t__ preserve_lightness; TYPE_3__ yellow_blue; TYPE_2__ magenta_green; TYPE_1__ cyan_red; } ;
typedef  TYPE_5__ ColorBalanceContext ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 float FFMAX3 (float,float,float) ; 
 float FFMIN3 (float,float,float) ; 
 float av_clip_uintp2_c (float,int const) ; 
 float get_component (float,float const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preservel (float*,float*,float*,float const) ; 

__attribute__((used)) static int color_balance16_p(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ColorBalanceContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;
    const int slice_start = (out->height * jobnr) / nb_jobs;
    const int slice_end = (out->height * (jobnr+1)) / nb_jobs;
    const uint16_t *srcg = (const uint16_t *)in->data[0] + slice_start * in->linesize[0] / 2;
    const uint16_t *srcb = (const uint16_t *)in->data[1] + slice_start * in->linesize[1] / 2;
    const uint16_t *srcr = (const uint16_t *)in->data[2] + slice_start * in->linesize[2] / 2;
    const uint16_t *srca = (const uint16_t *)in->data[3] + slice_start * in->linesize[3] / 2;
    uint16_t *dstg = (uint16_t *)out->data[0] + slice_start * out->linesize[0] / 2;
    uint16_t *dstb = (uint16_t *)out->data[1] + slice_start * out->linesize[1] / 2;
    uint16_t *dstr = (uint16_t *)out->data[2] + slice_start * out->linesize[2] / 2;
    uint16_t *dsta = (uint16_t *)out->data[3] + slice_start * out->linesize[3] / 2;
    const int depth = s->depth;
    const float max = s->max;
    int i, j;

    for (i = slice_start; i < slice_end; i++) {
        for (j = 0; j < out->width; j++) {
            float r = srcr[j] / max;
            float g = srcg[j] / max;
            float b = srcb[j] / max;
            const float l = (FFMAX3(r, g, b) + FFMIN3(r, g, b));

            r = get_component(r, l, s->cyan_red.shadows, s->cyan_red.midtones, s->cyan_red.highlights);
            g = get_component(g, l, s->magenta_green.shadows, s->magenta_green.midtones, s->magenta_green.highlights);
            b = get_component(b, l, s->yellow_blue.shadows, s->yellow_blue.midtones, s->yellow_blue.highlights);

            if (s->preserve_lightness)
                preservel(&r, &g, &b, l);

            dstr[j] = av_clip_uintp2_c(r * max, depth);
            dstg[j] = av_clip_uintp2_c(g * max, depth);
            dstb[j] = av_clip_uintp2_c(b * max, depth);
            if (in != out && out->linesize[3])
                dsta[j] = srca[j];
        }

        srcg += in->linesize[0] / 2;
        srcb += in->linesize[1] / 2;
        srcr += in->linesize[2] / 2;
        srca += in->linesize[3] / 2;
        dstg += out->linesize[0] / 2;
        dstb += out->linesize[1] / 2;
        dstr += out->linesize[2] / 2;
        dsta += out->linesize[3] / 2;
    }

    return 0;
}