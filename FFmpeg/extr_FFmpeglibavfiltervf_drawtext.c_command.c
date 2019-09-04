#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_7__ {int reinit; } ;
typedef  TYPE_1__ DrawTextContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int av_set_options_string (TYPE_2__*,char const*,char*,char*) ; 
 int config_input (int /*<<< orphan*/ ) ; 
 int init (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  uninit (TYPE_2__*) ; 

__attribute__((used)) static int command(AVFilterContext *ctx, const char *cmd, const char *arg, char *res, int res_len, int flags)
{
    DrawTextContext *s = ctx->priv;

    if (!strcmp(cmd, "reinit")) {
        int ret;
        uninit(ctx);
        s->reinit = 1;
        if ((ret = av_set_options_string(ctx, arg, "=", ":")) < 0)
            return ret;
        if ((ret = init(ctx)) < 0)
            return ret;
        return config_input(ctx->inputs[0]);
    }

    return AVERROR(ENOSYS);
}