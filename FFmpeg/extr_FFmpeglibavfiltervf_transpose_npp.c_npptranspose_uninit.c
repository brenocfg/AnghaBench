#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  frames_ctx; int /*<<< orphan*/  frame; } ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  tmp_frame; TYPE_4__* stages; } ;
typedef  TYPE_1__ NPPTransposeContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_4__*) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void npptranspose_uninit(AVFilterContext *ctx)
{
    NPPTransposeContext *s = ctx->priv;
    int i;

    for (i = 0; i < FF_ARRAY_ELEMS(s->stages); i++) {
        av_frame_free(&s->stages[i].frame);
        av_buffer_unref(&s->stages[i].frames_ctx);
    }

    av_frame_free(&s->tmp_frame);
}