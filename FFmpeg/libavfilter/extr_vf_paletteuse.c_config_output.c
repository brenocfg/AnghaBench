#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int opt_repeatlast; int /*<<< orphan*/  on_event; TYPE_1__* in; } ;
struct TYPE_14__ {TYPE_2__** inputs; TYPE_3__* priv; } ;
struct TYPE_13__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_5__* src; } ;
struct TYPE_12__ {TYPE_6__ fs; } ;
struct TYPE_11__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_10__ {int /*<<< orphan*/  after; int /*<<< orphan*/  before; } ;
typedef  TYPE_3__ PaletteUseContext ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_INFINITY ; 
 int ff_framesync_configure (TYPE_6__*) ; 
 int ff_framesync_init_dualinput (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  load_apply_palette ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    int ret;
    AVFilterContext *ctx = outlink->src;
    PaletteUseContext *s = ctx->priv;

    ret = ff_framesync_init_dualinput(&s->fs, ctx);
    if (ret < 0)
        return ret;
    s->fs.opt_repeatlast = 1; // only 1 frame in the palette
    s->fs.in[1].before = s->fs.in[1].after = EXT_INFINITY;
    s->fs.on_event = load_apply_palette;

    outlink->w = ctx->inputs[0]->w;
    outlink->h = ctx->inputs[0]->h;

    outlink->time_base = ctx->inputs[0]->time_base;
    if ((ret = ff_framesync_configure(&s->fs)) < 0)
        return ret;
    return 0;
}