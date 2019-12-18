#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_12__ {int reinit; int /*<<< orphan*/ * class; } ;
typedef  TYPE_1__ DrawTextContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* av_mallocz (int) ; 
 int av_opt_copy (TYPE_1__*,TYPE_1__*) ; 
 int av_set_options_string (TYPE_2__*,char const*,char*,char*) ; 
 int config_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drawtext_class ; 
 int init (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  uninit (TYPE_2__*) ; 

__attribute__((used)) static int command(AVFilterContext *ctx, const char *cmd, const char *arg, char *res, int res_len, int flags)
{
    DrawTextContext *old = ctx->priv;
    DrawTextContext *new = NULL;
    int ret;

    if (!strcmp(cmd, "reinit")) {
        new = av_mallocz(sizeof(DrawTextContext));
        if (!new)
            return AVERROR(ENOMEM);

        new->class = &drawtext_class;
        ret = av_opt_copy(new, old);
        if (ret < 0)
            goto fail;

        ctx->priv = new;
        ret = av_set_options_string(ctx, arg, "=", ":");
        if (ret < 0) {
            ctx->priv = old;
            goto fail;
        }

        ret = init(ctx);
        if (ret < 0) {
            uninit(ctx);
            ctx->priv = old;
            goto fail;
        }

        new->reinit = 1;

        ctx->priv = old;
        uninit(ctx);
        av_freep(&old);

        ctx->priv = new;
        return config_input(ctx->inputs[0]);
    } else
        return AVERROR(ENOSYS);

fail:
    av_log(ctx, AV_LOG_ERROR, "Failed to process command. Continuing with existing parameters.\n");
    av_freep(&new);
    return ret;
}