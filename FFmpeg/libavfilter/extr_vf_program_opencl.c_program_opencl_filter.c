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
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {TYPE_3__* parent; } ;
struct TYPE_6__ {int nb_inputs; int /*<<< orphan*/ * frames; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ ProgramOpenCLContext ;
typedef  TYPE_2__ FFFrameSync ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int ff_framesync_get_frame (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int program_opencl_run (TYPE_3__*) ; 

__attribute__((used)) static int program_opencl_filter(FFFrameSync *fs)
{
    AVFilterContext    *avctx = fs->parent;
    ProgramOpenCLContext *ctx = avctx->priv;
    int err, i;

    for (i = 0; i < ctx->nb_inputs; i++) {
        err = ff_framesync_get_frame(&ctx->fs, i, &ctx->frames[i], 0);
        if (err < 0)
            return err;
    }

    return program_opencl_run(avctx);
}