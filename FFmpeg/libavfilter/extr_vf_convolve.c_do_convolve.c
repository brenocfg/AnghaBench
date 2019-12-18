#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_32__ {int plane; int n; int /*<<< orphan*/ * vdata; int /*<<< orphan*/ * hdata; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_36__ {TYPE_1__* internal; TYPE_4__* priv; int /*<<< orphan*/ ** outputs; } ;
struct TYPE_35__ {int* linesize; scalar_t__* data; } ;
struct TYPE_34__ {int nb_planes; int* fft_len; int* planewidth; int* planeheight; int planes; int* got_impulse; int depth; int /*<<< orphan*/ ** fft_hdata; int /*<<< orphan*/ ** fft_vdata; int /*<<< orphan*/  filter; int /*<<< orphan*/ ** fft_vdata_impulse; int /*<<< orphan*/ ** fft_hdata_impulse; scalar_t__ impulse; } ;
struct TYPE_33__ {TYPE_6__* parent; } ;
struct TYPE_31__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  FFTComplex ;
typedef  TYPE_3__ FFFrameSync ;
typedef  TYPE_4__ ConvolveContext ;
typedef  TYPE_5__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 float FFMAX (int,float) ; 
 int /*<<< orphan*/  FFMIN3 (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_THREADS ; 
 int ff_filter_frame (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_6__*) ; 
 int ff_framesync_dualinput_get (TYPE_3__*,TYPE_5__**,TYPE_5__**) ; 
 int /*<<< orphan*/  fft_horizontal ; 
 int /*<<< orphan*/  fft_vertical ; 
 int /*<<< orphan*/  get_input (TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__*,int const,int const,int const,int,float) ; 
 int /*<<< orphan*/  get_output (TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__*,int const,int const,int const,int,float) ; 
 int /*<<< orphan*/  ifft_horizontal ; 
 int /*<<< orphan*/  ifft_vertical ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_convolve(FFFrameSync *fs)
{
    AVFilterContext *ctx = fs->parent;
    AVFilterLink *outlink = ctx->outputs[0];
    ConvolveContext *s = ctx->priv;
    AVFrame *mainpic = NULL, *impulsepic = NULL;
    int ret, y, x, plane;

    ret = ff_framesync_dualinput_get(fs, &mainpic, &impulsepic);
    if (ret < 0)
        return ret;
    if (!impulsepic)
        return ff_filter_frame(outlink, mainpic);

    for (plane = 0; plane < s->nb_planes; plane++) {
        FFTComplex *filter = s->fft_vdata_impulse[plane];
        FFTComplex *input = s->fft_vdata[plane];
        const int n = s->fft_len[plane];
        const int w = s->planewidth[plane];
        const int h = s->planeheight[plane];
        float total = 0;
        ThreadData td;

        if (!(s->planes & (1 << plane))) {
            continue;
        }

        td.plane = plane, td.n = n;
        get_input(s, s->fft_hdata[plane], mainpic, w, h, n, plane, 1.f);

        td.hdata = s->fft_hdata[plane];
        td.vdata = s->fft_vdata[plane];

        ctx->internal->execute(ctx, fft_horizontal, &td, NULL, FFMIN3(MAX_THREADS, n, ff_filter_get_nb_threads(ctx)));
        ctx->internal->execute(ctx, fft_vertical, &td, NULL, FFMIN3(MAX_THREADS, n, ff_filter_get_nb_threads(ctx)));

        if ((!s->impulse && !s->got_impulse[plane]) || s->impulse) {
            if (s->depth == 8) {
                for (y = 0; y < h; y++) {
                    const uint8_t *src = (const uint8_t *)(impulsepic->data[plane] + y * impulsepic->linesize[plane]) ;
                    for (x = 0; x < w; x++) {
                        total += src[x];
                    }
                }
            } else {
                for (y = 0; y < h; y++) {
                    const uint16_t *src = (const uint16_t *)(impulsepic->data[plane] + y * impulsepic->linesize[plane]) ;
                    for (x = 0; x < w; x++) {
                        total += src[x];
                    }
                }
            }
            total = FFMAX(1, total);

            get_input(s, s->fft_hdata_impulse[plane], impulsepic, w, h, n, plane, 1.f / total);

            td.hdata = s->fft_hdata_impulse[plane];
            td.vdata = s->fft_vdata_impulse[plane];

            ctx->internal->execute(ctx, fft_horizontal, &td, NULL, FFMIN3(MAX_THREADS, n, ff_filter_get_nb_threads(ctx)));
            ctx->internal->execute(ctx, fft_vertical, &td, NULL, FFMIN3(MAX_THREADS, n, ff_filter_get_nb_threads(ctx)));

            s->got_impulse[plane] = 1;
        }

        td.hdata = input;
        td.vdata = filter;

        ctx->internal->execute(ctx, s->filter, &td, NULL, FFMIN3(MAX_THREADS, n, ff_filter_get_nb_threads(ctx)));

        td.hdata = s->fft_hdata[plane];
        td.vdata = s->fft_vdata[plane];

        ctx->internal->execute(ctx, ifft_vertical, &td, NULL, FFMIN3(MAX_THREADS, n, ff_filter_get_nb_threads(ctx)));
        ctx->internal->execute(ctx, ifft_horizontal, &td, NULL, FFMIN3(MAX_THREADS, n, ff_filter_get_nb_threads(ctx)));

        get_output(s, s->fft_hdata[plane], mainpic, w, h, n, plane, 1.f / (n * n));
    }

    return ff_filter_frame(outlink, mainpic);
}