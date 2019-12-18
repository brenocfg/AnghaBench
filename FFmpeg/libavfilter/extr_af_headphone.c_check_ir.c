#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* priv; } ;
struct TYPE_10__ {TYPE_4__* dst; } ;
struct TYPE_9__ {int /*<<< orphan*/  ir_len; TYPE_1__* in; } ;
struct TYPE_8__ {int ir_len; } ;
typedef  TYPE_2__ HeadphoneContext ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int) ; 
 int ff_inlink_queued_samples (TYPE_3__*) ; 

__attribute__((used)) static int check_ir(AVFilterLink *inlink, int input_number)
{
    AVFilterContext *ctx = inlink->dst;
    HeadphoneContext *s = ctx->priv;
    int ir_len, max_ir_len;

    ir_len = ff_inlink_queued_samples(inlink);
    max_ir_len = 65536;
    if (ir_len > max_ir_len) {
        av_log(ctx, AV_LOG_ERROR, "Too big length of IRs: %d > %d.\n", ir_len, max_ir_len);
        return AVERROR(EINVAL);
    }
    s->in[input_number].ir_len = ir_len;
    s->ir_len = FFMAX(ir_len, s->ir_len);

    return 0;
}