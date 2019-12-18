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
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ filter_hw_device ; 
 scalar_t__ hw_device_get_by_name (char const*) ; 

__attribute__((used)) static int opt_filter_hw_device(void *optctx, const char *opt, const char *arg)
{
    if (filter_hw_device) {
        av_log(NULL, AV_LOG_ERROR, "Only one filter device can be used.\n");
        return AVERROR(EINVAL);
    }
    filter_hw_device = hw_device_get_by_name(arg);
    if (!filter_hw_device) {
        av_log(NULL, AV_LOG_ERROR, "Invalid filter device %s.\n", arg);
        return AVERROR(EINVAL);
    }
    return 0;
}