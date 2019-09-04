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
 int AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (void*,int,char*,int,char const*,double,...) ; 
 scalar_t__ isnan (double) ; 

__attribute__((used)) static double clip_with_log(void *log_ctx, const char *name,
                            double val, double min, double max,
                            double nan_replace, int idx)
{
    int level = AV_LOG_WARNING;
    if (isnan(val)) {
        av_log(log_ctx, level, "[%d] %s is nan, setting it to %g.\n",
               idx, name, nan_replace);
        val = nan_replace;
    } else if (val < min) {
        av_log(log_ctx, level, "[%d] %s is too low (%g), setting it to %g.\n",
               idx, name, val, min);
        val = min;
    } else if (val > max) {
        av_log(log_ctx, level, "[%d] %s it too high (%g), setting it to %g.\n",
               idx, name, val, max);
        val = max;
    }
    return val;
}