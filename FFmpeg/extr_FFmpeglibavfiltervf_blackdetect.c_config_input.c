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
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  format; TYPE_3__* dst; } ;
struct TYPE_6__ {int black_min_duration; int black_min_duration_time; int pixel_black_th_i; int pixel_black_th; int /*<<< orphan*/  picture_black_ratio_th; } ;
typedef  TYPE_1__ BlackDetectContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_ts2timestr (int,int /*<<< orphan*/ *) ; 
 scalar_t__ ff_fmt_is_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yuvj_formats ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    BlackDetectContext *blackdetect = ctx->priv;

    blackdetect->black_min_duration =
        blackdetect->black_min_duration_time / av_q2d(inlink->time_base);

    blackdetect->pixel_black_th_i = ff_fmt_is_in(inlink->format, yuvj_formats) ?
        // luminance_minimum_value + pixel_black_th * luminance_range_size
             blackdetect->pixel_black_th *  255 :
        16 + blackdetect->pixel_black_th * (235 - 16);

    av_log(blackdetect, AV_LOG_VERBOSE,
           "black_min_duration:%s pixel_black_th:%f pixel_black_th_i:%d picture_black_ratio_th:%f\n",
           av_ts2timestr(blackdetect->black_min_duration, &inlink->time_base),
           blackdetect->pixel_black_th, blackdetect->pixel_black_th_i,
           blackdetect->picture_black_ratio_th);
    return 0;
}