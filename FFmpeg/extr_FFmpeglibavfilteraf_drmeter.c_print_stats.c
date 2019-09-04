#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {double blknum; int* rms; scalar_t__* peaks; } ;
struct TYPE_7__ {int nb_channels; TYPE_2__* chstats; } ;
typedef  TYPE_1__ DRMeterContext ;
typedef  TYPE_2__ ChannelStats ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 float SQR (int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,float,...) ; 
 int /*<<< orphan*/  finish_block (TYPE_2__*) ; 
 int log10 (float) ; 
 float sqrt (float) ; 

__attribute__((used)) static void print_stats(AVFilterContext *ctx)
{
    DRMeterContext *s = ctx->priv;
    float dr = 0;
    int ch;

    for (ch = 0; ch < s->nb_channels; ch++) {
        ChannelStats *p = &s->chstats[ch];
        float chdr, secondpeak, rmssum = 0;
        int i, j, first = 0;

        finish_block(p);

        for (i = 0; i <= 10000; i++) {
            if (p->peaks[10000 - i]) {
                if (first)
                    break;
                first = 1;
            }
        }

        secondpeak = (10000 - i) / 10000.;

        for (i = 10000, j = 0; i >= 0 && j < 0.2 * p->blknum; i--) {
            if (p->rms[i]) {
                rmssum += SQR(i / 10000.) * p->rms[i];
                j += p->rms[i];
            }
        }

        chdr = 20 * log10(secondpeak / sqrt(rmssum / (0.2 * p->blknum)));
        dr += chdr;
        av_log(ctx, AV_LOG_INFO, "Channel %d: DR: %.1f\n", ch + 1, chdr);
    }

    av_log(ctx, AV_LOG_INFO, "Overall DR: %.1f\n", dr / s->nb_channels);
}