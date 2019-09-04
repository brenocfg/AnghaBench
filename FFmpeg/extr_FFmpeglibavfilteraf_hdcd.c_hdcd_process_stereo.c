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
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {int running_gain; int /*<<< orphan*/  sustain; } ;
struct TYPE_7__ {TYPE_3__* state; int /*<<< orphan*/  val_target_gain; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  analyze_mode; } ;
typedef  TYPE_1__ HDCDContext ;

/* Variables and functions */
 int HDCD_TG_MISMATCH ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int hdcd_analyze (int /*<<< orphan*/ *,int,int const,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdcd_analyze_prepare (TYPE_3__*,int /*<<< orphan*/ *,int,int const) ; 
 int hdcd_control_stereo (TYPE_1__*,int*,int*) ; 
 int hdcd_envelope (int /*<<< orphan*/ *,int,int const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int hdcd_scan (TYPE_1__*,TYPE_3__*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdcd_process_stereo(HDCDContext *ctx, int32_t *samples, int count)
{
    const int stride = 2;
    int32_t *samples_end = samples + count * stride;
    int gain[2] = {ctx->state[0].running_gain, ctx->state[1].running_gain};
    int peak_extend[2];
    int lead = 0;
    int ctlret;

    if (ctx->analyze_mode) {
        hdcd_analyze_prepare(&ctx->state[0], samples, count, stride);
        hdcd_analyze_prepare(&ctx->state[1], samples + 1, count, stride);
    }

    ctlret = hdcd_control_stereo(ctx, &peak_extend[0], &peak_extend[1]);
    while (count > lead) {
        int envelope_run, run;

        av_assert0(samples + lead * stride + stride * (count - lead) <= samples_end);
        run = hdcd_scan(ctx, ctx->state, 2, samples + lead * stride, count - lead, 0) + lead;
        envelope_run = run - 1;

        av_assert0(samples + envelope_run * stride <= samples_end);

        if (ctx->analyze_mode) {
            gain[0] = hdcd_analyze(samples, envelope_run, stride, gain[0], ctx->val_target_gain, peak_extend[0],
                ctx->analyze_mode,
                ctx->state[0].sustain,
                (ctlret == HDCD_TG_MISMATCH) );
            gain[1] = hdcd_analyze(samples + 1, envelope_run, stride, gain[1], ctx->val_target_gain, peak_extend[1],
                ctx->analyze_mode,
                ctx->state[1].sustain,
                (ctlret == HDCD_TG_MISMATCH) );
        } else {
            gain[0] = hdcd_envelope(samples, envelope_run, stride, ctx->bits_per_sample, gain[0], ctx->val_target_gain, peak_extend[0]);
            gain[1] = hdcd_envelope(samples + 1, envelope_run, stride, ctx->bits_per_sample, gain[1], ctx->val_target_gain, peak_extend[1]);
        }

        samples += envelope_run * stride;
        count -= envelope_run;
        lead = run - envelope_run;

        ctlret = hdcd_control_stereo(ctx, &peak_extend[0], &peak_extend[1]);
    }
    if (lead > 0) {
        av_assert0(samples + lead * stride <= samples_end);
        if (ctx->analyze_mode) {
            gain[0] = hdcd_analyze(samples, lead, stride, gain[0], ctx->val_target_gain, peak_extend[0],
                ctx->analyze_mode,
                ctx->state[0].sustain,
                (ctlret == HDCD_TG_MISMATCH) );
            gain[1] = hdcd_analyze(samples + 1, lead, stride, gain[1], ctx->val_target_gain, peak_extend[1],
                ctx->analyze_mode,
                ctx->state[1].sustain,
                (ctlret == HDCD_TG_MISMATCH) );
        } else {
            gain[0] = hdcd_envelope(samples, lead, stride, ctx->bits_per_sample, gain[0], ctx->val_target_gain, peak_extend[0]);
            gain[1] = hdcd_envelope(samples + 1, lead, stride, ctx->bits_per_sample, gain[1], ctx->val_target_gain, peak_extend[1]);
        }
    }

    ctx->state[0].running_gain = gain[0];
    ctx->state[1].running_gain = gain[1];
}