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
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int avfilter_config_links (int /*<<< orphan*/ *) ; 
 int parse_mapping (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int process_command(AVFilterContext *ctx, const char *cmd, const char *args,
                           char *res, int res_len, int flags)
{
    if (!strcmp(cmd, "map")) {
        int ret = parse_mapping(ctx, args);

        if (ret < 0)
            return ret;
        return avfilter_config_links(ctx);
    }
    return AVERROR(ENOSYS);
}