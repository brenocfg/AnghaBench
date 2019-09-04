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
 int AV_SAMPLE_FMT_NONE ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ av_get_bytes_per_sample (int) ; 
 int av_get_sample_fmt (char const*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

int ff_parse_sample_format(int *ret, const char *arg, void *log_ctx)
{
    char *tail;
    int sfmt = av_get_sample_fmt(arg);
    if (sfmt == AV_SAMPLE_FMT_NONE) {
        sfmt = strtol(arg, &tail, 0);
        if (*tail || av_get_bytes_per_sample(sfmt)<=0) {
            av_log(log_ctx, AV_LOG_ERROR, "Invalid sample format '%s'\n", arg);
            return AVERROR(EINVAL);
        }
    }
    *ret = sfmt;
    return 0;
}