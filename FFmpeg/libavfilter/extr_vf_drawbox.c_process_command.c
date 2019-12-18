#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv; int /*<<< orphan*/ ** inputs; } ;
struct TYPE_6__ {int x; int y; int w; int h; int thickness; int replace; } ;
typedef  TYPE_1__ DrawBoxContext ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int config_input (int /*<<< orphan*/ *) ; 
 int ff_filter_process_command (TYPE_2__*,char const*,char const*,char*,int,int) ; 
 int init (TYPE_2__*) ; 

__attribute__((used)) static int process_command(AVFilterContext *ctx, const char *cmd, const char *args, char *res, int res_len, int flags)
{
    AVFilterLink *inlink = ctx->inputs[0];
    DrawBoxContext *s = ctx->priv;
    int old_x = s->x;
    int old_y = s->y;
    int old_w = s->w;
    int old_h = s->h;
    int old_t = s->thickness;
    int old_r = s->replace;
    int ret;

    ret = ff_filter_process_command(ctx, cmd, args, res, res_len, flags);
    if (ret < 0)
        return ret;

    ret = init(ctx);
    if (ret < 0)
        goto end;
    ret = config_input(inlink);;
end:
    if (ret < 0) {
        s->x = old_x;
        s->y = old_y;
        s->w = old_w;
        s->h = old_h;
        s->thickness = old_t;
        s->replace = old_r;
    }

    return ret;
}