#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 double INT_MAX ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*) ; 
 double av_strtod (char const*,char**) ; 

int ff_parse_sample_rate(int *ret, const char *arg, void *log_ctx)
{
    char *tail;
    double srate = av_strtod(arg, &tail);
    if (*tail || srate < 1 || (int)srate != srate || srate > INT_MAX) {
        av_log(log_ctx, AV_LOG_ERROR, "Invalid sample rate '%s'\n", arg);
        return AVERROR(EINVAL);
    }
    *ret = srate;
    return 0;
}