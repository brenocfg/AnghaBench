#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ ** hp; int /*<<< orphan*/ ** lp; } ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int sample_rate; int channels; TYPE_3__* dst; } ;
struct TYPE_6__ {int order; int filter_count; int nb_splits; int /*<<< orphan*/ * splits; TYPE_5__* xover; } ;
typedef  TYPE_1__ AudioCrossoverContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 double M_SQRT1_2 ; 
 TYPE_5__* av_calloc (int,int) ; 
 int /*<<< orphan*/  set_hp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,int) ; 
 int /*<<< orphan*/  set_lp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,int) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    AudioCrossoverContext *s = ctx->priv;
    int ch, band, sample_rate = inlink->sample_rate;
    double q;

    s->xover = av_calloc(inlink->channels, sizeof(*s->xover));
    if (!s->xover)
        return AVERROR(ENOMEM);

    switch (s->order) {
    case 0:
        q = 0.5;
        s->filter_count = 1;
        break;
    case 1:
        q = M_SQRT1_2;
        s->filter_count = 2;
        break;
    case 2:
        q = 0.54;
        s->filter_count = 4;
        break;
    }

    for (ch = 0; ch < inlink->channels; ch++) {
        for (band = 0; band <= s->nb_splits; band++) {
            set_lp(&s->xover[ch].lp[band][0], s->splits[band], q, sample_rate);
            set_hp(&s->xover[ch].hp[band][0], s->splits[band], q, sample_rate);

            if (s->order > 1) {
                set_lp(&s->xover[ch].lp[band][1], s->splits[band], 1.34, sample_rate);
                set_hp(&s->xover[ch].hp[band][1], s->splits[band], 1.34, sample_rate);
                set_lp(&s->xover[ch].lp[band][2], s->splits[band],    q, sample_rate);
                set_hp(&s->xover[ch].hp[band][2], s->splits[band],    q, sample_rate);
                set_lp(&s->xover[ch].lp[band][3], s->splits[band], 1.34, sample_rate);
                set_hp(&s->xover[ch].hp[band][3], s->splits[band], 1.34, sample_rate);
            } else {
                set_lp(&s->xover[ch].lp[band][1], s->splits[band], q, sample_rate);
                set_hp(&s->xover[ch].hp[band][1], s->splits[band], q, sample_rate);
            }
        }
    }

    return 0;
}