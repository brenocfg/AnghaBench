#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* in; int /*<<< orphan*/ * on_event; TYPE_1__* opaque; } ;
struct TYPE_13__ {TYPE_3__** inputs; TYPE_1__* priv; } ;
struct TYPE_12__ {int /*<<< orphan*/  time_base; TYPE_4__* src; } ;
struct TYPE_11__ {int sync; int /*<<< orphan*/  after; int /*<<< orphan*/  before; int /*<<< orphan*/  time_base; } ;
struct TYPE_10__ {scalar_t__ nb_inputs; int /*<<< orphan*/  source_rate; TYPE_7__ fs; } ;
typedef  TYPE_1__ ProgramOpenCLContext ;
typedef  TYPE_2__ FFFrameSyncIn ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_INFINITY ; 
 int /*<<< orphan*/  EXT_STOP ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 int ff_framesync_configure (TYPE_7__*) ; 
 int ff_framesync_init (TYPE_7__*,TYPE_4__*,scalar_t__) ; 
 int ff_opencl_filter_config_output (TYPE_3__*) ; 
 int /*<<< orphan*/  program_opencl_filter ; 

__attribute__((used)) static int program_opencl_config_output(AVFilterLink *outlink)
{
    AVFilterContext    *avctx = outlink->src;
    ProgramOpenCLContext *ctx = avctx->priv;
    int err;

    err = ff_opencl_filter_config_output(outlink);
    if (err < 0)
        return err;

    if (ctx->nb_inputs > 0) {
        FFFrameSyncIn *in;
        int i;

        err = ff_framesync_init(&ctx->fs, avctx, ctx->nb_inputs);
        if (err < 0)
            return err;

        ctx->fs.opaque = ctx;
        ctx->fs.on_event = &program_opencl_filter;

        in = ctx->fs.in;
        for (i = 0; i < ctx->nb_inputs; i++) {
            const AVFilterLink *inlink = avctx->inputs[i];

            in[i].time_base = inlink->time_base;
            in[i].sync      = 1;
            in[i].before    = EXT_STOP;
            in[i].after     = EXT_INFINITY;
        }

        err = ff_framesync_configure(&ctx->fs);
        if (err < 0)
            return err;

    } else {
        outlink->time_base = av_inv_q(ctx->source_rate);
    }

    return 0;
}