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
struct TYPE_8__ {TYPE_3__* src; } ;
struct TYPE_7__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ OverlayOpenCLContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int ff_framesync_configure (int /*<<< orphan*/ *) ; 
 int ff_framesync_init_dualinput (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int ff_opencl_filter_config_output (TYPE_2__*) ; 

__attribute__((used)) static int overlay_opencl_config_output(AVFilterLink *outlink)
{
    AVFilterContext *avctx = outlink->src;
    OverlayOpenCLContext *ctx = avctx->priv;
    int err;

    err = ff_opencl_filter_config_output(outlink);
    if (err < 0)
        return err;

    err = ff_framesync_init_dualinput(&ctx->fs, avctx);
    if (err < 0)
        return err;

    return ff_framesync_configure(&ctx->fs);
}