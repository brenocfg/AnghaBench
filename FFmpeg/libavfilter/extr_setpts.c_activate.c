#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_18__ {TYPE_2__** outputs; TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_17__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_16__ {double* var_values; } ;
typedef  TYPE_1__ SetPTSContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  D2TS (double) ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_WANTED (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  TS2T (double,int /*<<< orphan*/ ) ; 
 size_t VAR_POS ; 
 size_t VAR_PTS ; 
 size_t VAR_T ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d2istr (double) ; 
 double eval_pts (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_inlink_acknowledge_status (TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int ff_inlink_consume_frame (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_outlink_set_status (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int filter_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    SetPTSContext *setpts = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *in;
    int status;
    int64_t pts;
    int ret;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    ret = ff_inlink_consume_frame(inlink, &in);
    if (ret < 0)
        return ret;
    if (ret > 0)
        return filter_frame(inlink, in);

    if (ff_inlink_acknowledge_status(inlink, &status, &pts)) {
        double d = eval_pts(setpts, inlink, NULL, pts);

        av_log(ctx, AV_LOG_TRACE, "N:EOF PTS:%s T:%f POS:%s -> PTS:%s T:%f\n",
               d2istr(setpts->var_values[VAR_PTS]),
               setpts->var_values[VAR_T],
               d2istr(setpts->var_values[VAR_POS]),
               d2istr(d), TS2T(d, inlink->time_base));
        ff_outlink_set_status(outlink, status, D2TS(d));
        return 0;
    }

    FF_FILTER_FORWARD_WANTED(outlink, inlink);

    return FFERROR_NOT_READY;
}