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
struct TYPE_7__ {TYPE_3__* dst; } ;
struct TYPE_6__ {int /*<<< orphan*/ * phase; } ;
typedef  TYPE_1__ SpectrumSynthContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int try_push_frames (TYPE_3__*) ; 

__attribute__((used)) static int filter_frame_phase(AVFilterLink *inlink, AVFrame *phase)
{
    AVFilterContext *ctx = inlink->dst;
    SpectrumSynthContext *s = ctx->priv;

    s->phase = phase;
    return try_push_frames(ctx);
}