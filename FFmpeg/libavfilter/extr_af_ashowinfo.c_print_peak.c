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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 float UINT32_MAX ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void print_peak(AVFilterContext *ctx, const char *str, uint32_t peak)
{
    av_log(ctx, AV_LOG_INFO, "%s - ", str);
    if (!peak)
        av_log(ctx, AV_LOG_INFO, "unknown");
    else
        av_log(ctx, AV_LOG_INFO, "%f", (float)peak / UINT32_MAX);
    av_log(ctx, AV_LOG_INFO, ", ");
}