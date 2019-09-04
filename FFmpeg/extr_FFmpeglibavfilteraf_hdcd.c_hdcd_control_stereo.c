#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hdcd_control_result ;
struct TYPE_4__ {int val_target_gain; int /*<<< orphan*/  sample_count; int /*<<< orphan*/  fctx; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ HDCDContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  GAINTOFLOAT (int) ; 
 int /*<<< orphan*/  HDCD_OK ; 
 int /*<<< orphan*/  HDCD_TG_MISMATCH ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdcd_control (TYPE_1__*,int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static hdcd_control_result hdcd_control_stereo(HDCDContext *ctx, int *peak_extend0, int *peak_extend1)
{
    int target_gain[2];
    hdcd_control(ctx, &ctx->state[0], peak_extend0, &target_gain[0]);
    hdcd_control(ctx, &ctx->state[1], peak_extend1, &target_gain[1]);
    if (target_gain[0] == target_gain[1])
        ctx->val_target_gain = target_gain[0];
    else {
        av_log(ctx->fctx, AV_LOG_VERBOSE,
           "hdcd error: Unmatched target_gain near %d: tg0: %0.1f, tg1: %0.1f, lvg: %0.1f\n",
           ctx->sample_count,
           GAINTOFLOAT(target_gain[0] >>7),
           GAINTOFLOAT(target_gain[1] >>7),
           GAINTOFLOAT(ctx->val_target_gain >>7) );
           return HDCD_TG_MISMATCH;
    }
    return HDCD_OK;
}