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
struct TYPE_8__ {TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_7__ {int channels; TYPE_3__* src; } ;
struct TYPE_6__ {scalar_t__ hrir_fmt; int gain; int lfe_gain; int /*<<< orphan*/  gain_lfe; } ;
typedef  TYPE_1__ HeadphoneContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ HRIR_MULTI ; 
 int M_LN10 ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  expf (int) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    HeadphoneContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];

    if (s->hrir_fmt == HRIR_MULTI) {
        AVFilterLink *hrir_link = ctx->inputs[1];

        if (hrir_link->channels < inlink->channels * 2) {
            av_log(ctx, AV_LOG_ERROR, "Number of channels in HRIR stream must be >= %d.\n", inlink->channels * 2);
            return AVERROR(EINVAL);
        }
    }

    s->gain_lfe = expf((s->gain - 3 * inlink->channels + s->lfe_gain) / 20 * M_LN10);

    return 0;
}