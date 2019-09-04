#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  on_event; } ;
struct TYPE_10__ {TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  time_base; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_3__* src; } ;
struct TYPE_8__ {int nb_planes; void*** ifft; void*** fft; int /*<<< orphan*/ * fft_bits; TYPE_4__ fs; } ;
typedef  TYPE_1__ ConvolveContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAX_THREADS ; 
 void* av_fft_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_convolve ; 
 int ff_framesync_configure (TYPE_4__*) ; 
 int ff_framesync_init_dualinput (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    ConvolveContext *s = ctx->priv;
    AVFilterLink *mainlink = ctx->inputs[0];
    int ret, i, j;

    s->fs.on_event = do_convolve;
    ret = ff_framesync_init_dualinput(&s->fs, ctx);
    if (ret < 0)
        return ret;
    outlink->w = mainlink->w;
    outlink->h = mainlink->h;
    outlink->time_base = mainlink->time_base;
    outlink->sample_aspect_ratio = mainlink->sample_aspect_ratio;
    outlink->frame_rate = mainlink->frame_rate;

    if ((ret = ff_framesync_configure(&s->fs)) < 0)
        return ret;

    for (i = 0; i < s->nb_planes; i++) {
        for (j = 0; j < MAX_THREADS; j++) {
            s->fft[i][j]  = av_fft_init(s->fft_bits[i], 0);
            s->ifft[i][j] = av_fft_init(s->fft_bits[i], 1);
            if (!s->fft[i][j] || !s->ifft[i][j])
                return AVERROR(ENOMEM);
        }
    }

    return 0;
}