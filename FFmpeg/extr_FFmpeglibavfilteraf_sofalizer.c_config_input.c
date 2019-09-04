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
struct TYPE_8__ {int channels; int /*<<< orphan*/  sample_rate; TYPE_3__* dst; } ;
struct TYPE_7__ {scalar_t__ type; int gain; int lfe_gain; int n_conv; int /*<<< orphan*/  buffer_length; int /*<<< orphan*/  radius; int /*<<< orphan*/  elevation; int /*<<< orphan*/  rotation; int /*<<< orphan*/  gain_lfe; int /*<<< orphan*/  framesize; int /*<<< orphan*/  nb_samples; } ;
typedef  TYPE_1__ SOFAlizerContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 scalar_t__ FREQUENCY_DOMAIN ; 
 int M_LN10 ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expf (int) ; 
 int load_data (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    SOFAlizerContext *s = ctx->priv;
    int ret;

    if (s->type == FREQUENCY_DOMAIN)
        s->nb_samples = s->framesize;

    /* gain -3 dB per channel */
    s->gain_lfe = expf((s->gain - 3 * inlink->channels + s->lfe_gain) / 20 * M_LN10);

    s->n_conv = inlink->channels;

    /* load IRs to data_ir[0] and data_ir[1] for required directions */
    if ((ret = load_data(ctx, s->rotation, s->elevation, s->radius, inlink->sample_rate)) < 0)
        return ret;

    av_log(ctx, AV_LOG_DEBUG, "Samplerate: %d Channels to convolute: %d, Length of ringbuffer: %d x %d\n",
        inlink->sample_rate, s->n_conv, inlink->channels, s->buffer_length);

    return 0;
}