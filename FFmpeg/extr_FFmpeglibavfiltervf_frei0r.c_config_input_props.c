#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_3__* dst; } ;
struct TYPE_7__ {int /*<<< orphan*/  params; scalar_t__ (* construct ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ instance; int /*<<< orphan*/  (* destruct ) (scalar_t__) ;} ;
typedef  TYPE_1__ Frei0rContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int set_params (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input_props(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    Frei0rContext *s = ctx->priv;

    if (s->destruct && s->instance)
        s->destruct(s->instance);
    if (!(s->instance = s->construct(inlink->w, inlink->h))) {
        av_log(ctx, AV_LOG_ERROR, "Impossible to load frei0r instance.\n");
        return AVERROR(EINVAL);
    }

    return set_params(ctx, s->params);
}