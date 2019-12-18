#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  float uint16_t ;
struct TYPE_13__ {TYPE_6__* out; TYPE_6__* in; } ;
typedef  TYPE_4__ ThreadData ;
struct TYPE_17__ {TYPE_7__** outputs; TYPE_5__* priv; } ;
struct TYPE_16__ {int const w; } ;
struct TYPE_15__ {int height; int const* linesize; scalar_t__* data; } ;
struct TYPE_12__ {int /*<<< orphan*/  highlights; int /*<<< orphan*/  midtones; int /*<<< orphan*/  shadows; } ;
struct TYPE_11__ {int /*<<< orphan*/  highlights; int /*<<< orphan*/  midtones; int /*<<< orphan*/  shadows; } ;
struct TYPE_10__ {int /*<<< orphan*/  highlights; int /*<<< orphan*/  midtones; int /*<<< orphan*/  shadows; } ;
struct TYPE_14__ {int* rgba_map; int step; int depth; float max; scalar_t__ preserve_lightness; TYPE_3__ yellow_blue; TYPE_2__ magenta_green; TYPE_1__ cyan_red; } ;
typedef  TYPE_5__ ColorBalanceContext ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVFilterLink ;
typedef  TYPE_8__ AVFilterContext ;

/* Variables and functions */
 size_t A ; 
 size_t B ; 
 float FFMAX3 (float,float,float) ; 
 float FFMIN3 (float,float,float) ; 
 size_t G ; 
 size_t R ; 
 float av_clip_uintp2_c (float,int const) ; 
 float get_component (float,float const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preservel (float*,float*,float*,float const) ; 

__attribute__((used)) static int color_balance16(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ColorBalanceContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;
    AVFilterLink *outlink = ctx->outputs[0];
    const int slice_start = (out->height * jobnr) / nb_jobs;
    const int slice_end = (out->height * (jobnr+1)) / nb_jobs;
    const uint16_t *srcrow = (const uint16_t *)in->data[0] + slice_start * in->linesize[0] / 2;
    const uint8_t roffset = s->rgba_map[R];
    const uint8_t goffset = s->rgba_map[G];
    const uint8_t boffset = s->rgba_map[B];
    const uint8_t aoffset = s->rgba_map[A];
    const int step = s->step / 2;
    const int depth = s->depth;
    const float max = s->max;
    uint16_t *dstrow;
    int i, j;

    dstrow = (uint16_t *)out->data[0] + slice_start * out->linesize[0] / 2;
    for (i = slice_start; i < slice_end; i++) {
        const uint16_t *src = srcrow;
        uint16_t *dst = dstrow;

        for (j = 0; j < outlink->w * step; j += step) {
            float r = src[j + roffset] / max;
            float g = src[j + goffset] / max;
            float b = src[j + boffset] / max;
            const float l = (FFMAX3(r, g, b) + FFMIN3(r, g, b));

            r = get_component(r, l, s->cyan_red.shadows, s->cyan_red.midtones, s->cyan_red.highlights);
            g = get_component(g, l, s->magenta_green.shadows, s->magenta_green.midtones, s->magenta_green.highlights);
            b = get_component(b, l, s->yellow_blue.shadows, s->yellow_blue.midtones, s->yellow_blue.highlights);

            if (s->preserve_lightness)
                preservel(&r, &g, &b, l);

            dst[j + roffset] = av_clip_uintp2_c(r * max, depth);
            dst[j + goffset] = av_clip_uintp2_c(g * max, depth);
            dst[j + boffset] = av_clip_uintp2_c(b * max, depth);
            if (in != out && step == 4)
                dst[j + aoffset] = src[j + aoffset];
        }

        srcrow += in->linesize[0] / 2;
        dstrow += out->linesize[0] / 2;
    }

    return 0;
}