#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_9__ {int use_frc; scalar_t__ out_height; scalar_t__ out_width; scalar_t__ crop_x; scalar_t__ crop_y; scalar_t__ crop_w; scalar_t__ crop_h; scalar_t__ use_crop; TYPE_7__ framerate; } ;
typedef  TYPE_1__ VPPContext ;
struct TYPE_11__ {TYPE_1__* priv; } ;
struct TYPE_10__ {scalar_t__ w; scalar_t__ h; TYPE_7__ frame_rate; TYPE_3__* dst; } ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 void* FFMAX (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ av_cmp_q (TYPE_7__,TYPE_7__) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int eval_expr (TYPE_3__*) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    VPPContext      *vpp = ctx->priv;
    int              ret;

    if (vpp->framerate.den == 0 || vpp->framerate.num == 0)
        vpp->framerate = inlink->frame_rate;

    if (av_cmp_q(vpp->framerate, inlink->frame_rate))
        vpp->use_frc = 1;

    ret = eval_expr(ctx);
    if (ret != 0) {
        av_log(ctx, AV_LOG_ERROR, "Fail to eval expr.\n");
        return ret;
    }

    if (vpp->out_height == 0 || vpp->out_width == 0) {
        vpp->out_width  = inlink->w;
        vpp->out_height = inlink->h;
    }

    if (vpp->use_crop) {
        vpp->crop_x = FFMAX(vpp->crop_x, 0);
        vpp->crop_y = FFMAX(vpp->crop_y, 0);

        if(vpp->crop_w + vpp->crop_x > inlink->w)
           vpp->crop_x = inlink->w - vpp->crop_w;
        if(vpp->crop_h + vpp->crop_y > inlink->h)
           vpp->crop_y = inlink->h - vpp->crop_h;
    }

    return 0;
}