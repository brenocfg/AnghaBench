#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVDurationEstimationMethod { ____Placeholder_AVDurationEstimationMethod } AVDurationEstimationMethod ;
struct TYPE_3__ {int duration_estimation_method; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */

enum AVDurationEstimationMethod av_fmt_ctx_get_duration_estimation_method(const AVFormatContext* ctx)
{
    return ctx->duration_estimation_method;
}