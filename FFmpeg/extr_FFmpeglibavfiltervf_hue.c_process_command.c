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
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  brightness_expr; int /*<<< orphan*/  brightness_pexpr; int /*<<< orphan*/  saturation_expr; int /*<<< orphan*/  saturation_pexpr; int /*<<< orphan*/  hue_deg_expr; int /*<<< orphan*/  hue_expr; int /*<<< orphan*/  hue_pexpr; int /*<<< orphan*/  hue_deg_pexpr; } ;
typedef  TYPE_1__ HueContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int set_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int process_command(AVFilterContext *ctx, const char *cmd, const char *args,
                           char *res, int res_len, int flags)
{
    HueContext *hue = ctx->priv;
    int ret;

#define SET_EXPR(expr, option)                                          \
    do {                                                                \
        ret = set_expr(&hue->expr##_pexpr, &hue->expr##_expr,           \
                       args, option, ctx);                              \
        if (ret < 0)                                                    \
            return ret;                                                 \
    } while (0)

    if (!strcmp(cmd, "h")) {
        SET_EXPR(hue_deg, "h");
        av_freep(&hue->hue_expr);
    } else if (!strcmp(cmd, "H")) {
        SET_EXPR(hue, "H");
        av_freep(&hue->hue_deg_expr);
    } else if (!strcmp(cmd, "s")) {
        SET_EXPR(saturation, "s");
    } else if (!strcmp(cmd, "b")) {
        SET_EXPR(brightness, "b");
    } else
        return AVERROR(ENOSYS);

    return 0;
}