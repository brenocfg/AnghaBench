#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int finished; int /*<<< orphan*/  y_expr_str; int /*<<< orphan*/  y_expr; int /*<<< orphan*/  x_expr_str; int /*<<< orphan*/  x_expr; int /*<<< orphan*/  zoom_expr_str; int /*<<< orphan*/  zoom_expr; int /*<<< orphan*/  desc; int /*<<< orphan*/  framerate; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ ZPContext ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  format; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  time_base; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_3__* src; } ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int av_expr_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_names ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    ZPContext *s = ctx->priv;
    int ret;

    outlink->w = s->w;
    outlink->h = s->h;
    outlink->time_base = av_inv_q(s->framerate);
    outlink->frame_rate = s->framerate;
    s->desc = av_pix_fmt_desc_get(outlink->format);
    s->finished = 1;

    ret = av_expr_parse(&s->zoom_expr, s->zoom_expr_str, var_names, NULL, NULL, NULL, NULL, 0, ctx);
    if (ret < 0)
        return ret;

    ret = av_expr_parse(&s->x_expr, s->x_expr_str, var_names, NULL, NULL, NULL, NULL, 0, ctx);
    if (ret < 0)
        return ret;

    ret = av_expr_parse(&s->y_expr, s->y_expr_str, var_names, NULL, NULL, NULL, NULL, 0, ctx);
    if (ret < 0)
        return ret;

    return 0;
}