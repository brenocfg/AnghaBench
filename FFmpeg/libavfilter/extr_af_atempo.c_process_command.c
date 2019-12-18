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
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int ff_filter_process_command (int /*<<< orphan*/ *,char const*,char const*,char*,int,int) ; 
 int yae_update (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_command(AVFilterContext *ctx,
                           const char *cmd,
                           const char *arg,
                           char *res,
                           int res_len,
                           int flags)
{
    int ret = ff_filter_process_command(ctx, cmd, arg, res, res_len, flags);

    if (ret < 0)
        return ret;

    return yae_update(ctx);
}