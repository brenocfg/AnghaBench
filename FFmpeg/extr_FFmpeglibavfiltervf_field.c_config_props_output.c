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
struct TYPE_8__ {TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_7__ {int h; int /*<<< orphan*/  w; int /*<<< orphan*/  format; TYPE_3__* src; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  nb_planes; } ;
typedef  TYPE_1__ FieldContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 scalar_t__ FIELD_TYPE_BOTTOM ; 
 scalar_t__ FIELD_TYPE_TOP ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_props_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    FieldContext *field = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];

    field->nb_planes = av_pix_fmt_count_planes(outlink->format);

    outlink->w = inlink->w;
    outlink->h = (inlink->h + (field->type == FIELD_TYPE_TOP)) / 2;

    av_log(ctx, AV_LOG_VERBOSE, "w:%d h:%d type:%s -> w:%d h:%d\n",
           inlink->w, inlink->h, field->type == FIELD_TYPE_BOTTOM ? "bottom" : "top",
           outlink->w, outlink->h);
    return 0;
}