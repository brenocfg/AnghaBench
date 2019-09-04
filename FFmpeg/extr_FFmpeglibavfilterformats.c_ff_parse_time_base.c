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
struct TYPE_4__ {scalar_t__ num; scalar_t__ den; } ;
typedef  TYPE_1__ AVRational ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ av_parse_ratio (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int ff_parse_time_base(AVRational *ret, const char *arg, void *log_ctx)
{
    AVRational r;
    if(av_parse_ratio(&r, arg, INT_MAX, 0, log_ctx) < 0 ||r.num<=0  ||r.den<=0) {
        av_log(log_ctx, AV_LOG_ERROR, "Invalid time base '%s'\n", arg);
        return AVERROR(EINVAL);
    }
    *ret = r;
    return 0;
}