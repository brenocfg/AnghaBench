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
struct TYPE_4__ {int /*<<< orphan*/ ** outputs; } ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_1__ AVFilterContext ;

/* Variables and functions */
 int config_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_filter_process_command (TYPE_1__*,char const*,char const*,char*,int,int) ; 

__attribute__((used)) static int process_command(AVFilterContext *ctx, const char *cmd, const char *args,
                           char *res, int res_len, int flags)
{
    AVFilterLink *outlink = ctx->outputs[0];
    int ret;

    ret = ff_filter_process_command(ctx, cmd, args, res, res_len, flags);
    if (ret < 0)
        return ret;

    return config_filter(outlink, 0);
}