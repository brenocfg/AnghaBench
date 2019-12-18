#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  sample_rate; } ;
struct TYPE_8__ {scalar_t__ orientation; int channel_height; int channel_width; scalar_t__ mode; float** color_buffer; } ;
typedef  TYPE_1__ ShowSpectrumContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ COMBINED ; 
 int FFMIN (int,int const) ; 
 scalar_t__ VERTICAL ; 
 float bin_pos (int,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_range (TYPE_1__*,int const,float*,float*,float*) ; 
 float get_value (TYPE_3__*,int const,int) ; 
 int lrintf (float) ; 
 int /*<<< orphan*/  pick_color (TYPE_1__*,float,float,float,float,float*) ; 

__attribute__((used)) static int plot_channel_log(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ShowSpectrumContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    const int h = s->orientation == VERTICAL ? s->channel_height : s->channel_width;
    const int ch = jobnr;
    float y, yf, uf, vf;
    int yy = 0;

    /* decide color range */
    color_range(s, ch, &yf, &uf, &vf);

    /* draw the channel */
    for (y = 0; y < h && yy < h; yy++) {
        float pos0 = bin_pos(yy+0, h, inlink->sample_rate);
        float pos1 = bin_pos(yy+1, h, inlink->sample_rate);
        float delta = pos1 - pos0;
        float a0, a1;

        a0 = get_value(ctx, ch, yy+0);
        a1 = get_value(ctx, ch, FFMIN(yy+1, h-1));
        for (float j = pos0; j < pos1 && y + j - pos0 < h; j++) {
            float row = (s->mode == COMBINED) ? y + j - pos0 : ch * h + y + j - pos0;
            float *out = &s->color_buffer[ch][3 * FFMIN(lrintf(row), h-1)];
            float lerpfrac = (j - pos0) / delta;

            pick_color(s, yf, uf, vf, lerpfrac * a1 + (1.f-lerpfrac) * a0, out);
        }
        y += delta;
    }

    return 0;
}