#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int w; int h; } ;
typedef  TYPE_1__ ZScaleContext ;
struct TYPE_6__ {int /*<<< orphan*/ ** outputs; TYPE_1__* priv; } ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_opt_set (TYPE_1__*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int config_props (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int process_command(AVFilterContext *ctx, const char *cmd, const char *args,
                           char *res, int res_len, int flags)
{
    ZScaleContext *s = ctx->priv;
    int ret;

    if (   !strcmp(cmd, "width")  || !strcmp(cmd, "w")
        || !strcmp(cmd, "height") || !strcmp(cmd, "h")) {

        int old_w = s->w;
        int old_h = s->h;
        AVFilterLink *outlink = ctx->outputs[0];

        av_opt_set(s, cmd, args, 0);
        if ((ret = config_props(outlink)) < 0) {
            s->w = old_w;
            s->h = old_h;
        }
    } else
        ret = AVERROR(ENOSYS);

    return ret;
}