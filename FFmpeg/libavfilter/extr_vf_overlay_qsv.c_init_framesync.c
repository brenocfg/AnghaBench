#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* in; TYPE_2__* opaque; int /*<<< orphan*/  on_event; } ;
struct TYPE_12__ {int nb_inputs; TYPE_1__** inputs; TYPE_2__* priv; } ;
struct TYPE_11__ {int sync; int /*<<< orphan*/  time_base; int /*<<< orphan*/  after; int /*<<< orphan*/  before; } ;
struct TYPE_10__ {TYPE_6__ fs; } ;
struct TYPE_9__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_2__ QSVOverlayContext ;
typedef  TYPE_3__ FFFrameSyncIn ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_INFINITY ; 
 int /*<<< orphan*/  EXT_STOP ; 
 int ff_framesync_configure (TYPE_6__*) ; 
 int ff_framesync_init (TYPE_6__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  process_frame ; 

__attribute__((used)) static int init_framesync(AVFilterContext *ctx)
{
    QSVOverlayContext *s = ctx->priv;
    int ret, i;

    s->fs.on_event = process_frame;
    s->fs.opaque   = s;
    ret = ff_framesync_init(&s->fs, ctx, ctx->nb_inputs);
    if (ret < 0)
        return ret;

    for (i = 0; i < ctx->nb_inputs; i++) {
        FFFrameSyncIn *in = &s->fs.in[i];
        in->before    = EXT_STOP;
        in->after     = EXT_INFINITY;
        in->sync      = i ? 1 : 2;
        in->time_base = ctx->inputs[i]->time_base;
    }

    return ff_framesync_configure(&s->fs);
}