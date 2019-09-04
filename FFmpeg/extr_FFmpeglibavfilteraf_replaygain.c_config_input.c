#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int sample_rate; int /*<<< orphan*/  BButter; int /*<<< orphan*/  AButter; int /*<<< orphan*/  BYule; int /*<<< orphan*/  AYule; } ;
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {int sample_rate; int partial_buf_size; int min_samples; int max_samples; TYPE_3__* dst; } ;
struct TYPE_7__ {int yule_hist_i; int butter_hist_i; int /*<<< orphan*/  butter_coeff_b; int /*<<< orphan*/  butter_coeff_a; int /*<<< orphan*/  yule_coeff_b; int /*<<< orphan*/  yule_coeff_a; } ;
typedef  TYPE_1__ ReplayGainContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_4__*) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_4__* freqinfos ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    ReplayGainContext *s = ctx->priv;
    int i;

    for (i = 0; i < FF_ARRAY_ELEMS(freqinfos); i++) {
        if (freqinfos[i].sample_rate == inlink->sample_rate)
            break;
    }
    av_assert0(i < FF_ARRAY_ELEMS(freqinfos));

    s->yule_coeff_a   = freqinfos[i].AYule;
    s->yule_coeff_b   = freqinfos[i].BYule;
    s->butter_coeff_a = freqinfos[i].AButter;
    s->butter_coeff_b = freqinfos[i].BButter;

    s->yule_hist_i   = 20;
    s->butter_hist_i = 4;
    inlink->partial_buf_size =
    inlink->min_samples =
    inlink->max_samples = inlink->sample_rate / 20;

    return 0;
}