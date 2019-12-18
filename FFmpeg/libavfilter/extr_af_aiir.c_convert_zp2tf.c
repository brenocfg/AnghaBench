#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {TYPE_1__* iir; } ;
struct TYPE_6__ {int* nb_ab; double** ab; } ;
typedef  TYPE_1__ IIRChannel ;
typedef  TYPE_2__ AudioIIRContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 double* av_calloc (int,int) ; 
 int /*<<< orphan*/  av_free (double*) ; 
 int expand (TYPE_3__*,double*,int,double*) ; 

__attribute__((used)) static int convert_zp2tf(AVFilterContext *ctx, int channels)
{
    AudioIIRContext *s = ctx->priv;
    int ch, i, j, ret = 0;

    for (ch = 0; ch < channels; ch++) {
        IIRChannel *iir = &s->iir[ch];
        double *topc, *botc;

        topc = av_calloc((iir->nb_ab[0] + 1) * 2, sizeof(*topc));
        botc = av_calloc((iir->nb_ab[1] + 1) * 2, sizeof(*botc));
        if (!topc || !botc) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        ret = expand(ctx, iir->ab[0], iir->nb_ab[0], botc);
        if (ret < 0) {
            goto fail;
        }

        ret = expand(ctx, iir->ab[1], iir->nb_ab[1], topc);
        if (ret < 0) {
            goto fail;
        }

        for (j = 0, i = iir->nb_ab[1]; i >= 0; j++, i--) {
            iir->ab[1][j] = topc[2 * i];
        }
        iir->nb_ab[1]++;

        for (j = 0, i = iir->nb_ab[0]; i >= 0; j++, i--) {
            iir->ab[0][j] = botc[2 * i];
        }
        iir->nb_ab[0]++;

fail:
        av_free(topc);
        av_free(botc);
        if (ret < 0)
            break;
    }

    return ret;
}