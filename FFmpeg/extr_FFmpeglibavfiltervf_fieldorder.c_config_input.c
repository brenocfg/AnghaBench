#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  w; int /*<<< orphan*/  format; TYPE_3__* dst; } ;
struct TYPE_5__ {int /*<<< orphan*/  line_size; } ;
typedef  TYPE_1__ FieldOrderContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int av_image_fill_linesizes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext   *ctx = inlink->dst;
    FieldOrderContext *s   = ctx->priv;

    return av_image_fill_linesizes(s->line_size, inlink->format, inlink->w);
}