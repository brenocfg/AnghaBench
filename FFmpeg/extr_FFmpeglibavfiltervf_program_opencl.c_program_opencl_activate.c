#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {scalar_t__ nb_inputs; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ ProgramOpenCLContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 int ff_framesync_activate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int program_opencl_activate(AVFilterContext *avctx)
{
    ProgramOpenCLContext *ctx = avctx->priv;

    av_assert0(ctx->nb_inputs > 0);

    return ff_framesync_activate(&ctx->fs);
}