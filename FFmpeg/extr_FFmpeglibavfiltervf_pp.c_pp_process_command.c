#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode_id; } ;
typedef  TYPE_1__ PPFilterContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  PP_QUALITY_MAX ; 
 int /*<<< orphan*/  av_clip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strtol (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pp_process_command(AVFilterContext *ctx, const char *cmd, const char *args,
                              char *res, int res_len, int flags)
{
    PPFilterContext *pp = ctx->priv;

    if (!strcmp(cmd, "quality")) {
        pp->mode_id = av_clip(strtol(args, NULL, 10), 0, PP_QUALITY_MAX);
        return 0;
    }
    return AVERROR(ENOSYS);
}