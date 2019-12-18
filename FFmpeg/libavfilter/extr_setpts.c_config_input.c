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
struct TYPE_9__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {scalar_t__ type; void* sample_rate; int /*<<< orphan*/  src; TYPE_5__ frame_rate; TYPE_5__ time_base; TYPE_3__* dst; } ;
struct TYPE_6__ {scalar_t__ type; void** var_values; } ;
typedef  TYPE_1__ SetPTSContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 void* NAN ; 
 size_t VAR_FR ; 
 size_t VAR_FRAME_RATE ; 
 size_t VAR_RTCSTART ; 
 size_t VAR_SAMPLE_RATE ; 
 size_t VAR_SR ; 
 size_t VAR_TB ; 
 void* av_gettime () ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*,void*,void*) ; 
 void* av_q2d (TYPE_5__) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    SetPTSContext *setpts = ctx->priv;

    setpts->type = inlink->type;
    setpts->var_values[VAR_TB] = av_q2d(inlink->time_base);
    setpts->var_values[VAR_RTCSTART] = av_gettime();

    setpts->var_values[VAR_SR] =
    setpts->var_values[VAR_SAMPLE_RATE] =
        setpts->type == AVMEDIA_TYPE_AUDIO ? inlink->sample_rate : NAN;

    setpts->var_values[VAR_FRAME_RATE] =
    setpts->var_values[VAR_FR] =         inlink->frame_rate.num &&
                                         inlink->frame_rate.den ?
                                            av_q2d(inlink->frame_rate) : NAN;

    av_log(inlink->src, AV_LOG_VERBOSE, "TB:%f FRAME_RATE:%f SAMPLE_RATE:%f\n",
           setpts->var_values[VAR_TB],
           setpts->var_values[VAR_FRAME_RATE],
           setpts->var_values[VAR_SAMPLE_RATE]);
    return 0;
}