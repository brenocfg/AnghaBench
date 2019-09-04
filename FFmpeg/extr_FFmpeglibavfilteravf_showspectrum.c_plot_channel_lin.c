#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {scalar_t__ orientation; int channel_height; int channel_width; scalar_t__ mode; float** color_buffer; } ;
typedef  TYPE_1__ ShowSpectrumContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ COMBINED ; 
 scalar_t__ VERTICAL ; 
 int /*<<< orphan*/  color_range (TYPE_1__*,int const,float*,float*,float*) ; 
 float get_value (TYPE_2__*,int const,int) ; 
 int /*<<< orphan*/  pick_color (TYPE_1__*,float,float,float,float,float*) ; 

__attribute__((used)) static int plot_channel_lin(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ShowSpectrumContext *s = ctx->priv;
    const int h = s->orientation == VERTICAL ? s->channel_height : s->channel_width;
    const int ch = jobnr;
    float yf, uf, vf;
    int y;

    /* decide color range */
    color_range(s, ch, &yf, &uf, &vf);

    /* draw the channel */
    for (y = 0; y < h; y++) {
        int row = (s->mode == COMBINED) ? y : ch * h + y;
        float *out = &s->color_buffer[ch][3 * row];
        float a = get_value(ctx, ch, y);

        pick_color(s, yf, uf, vf, a, out);
    }

    return 0;
}