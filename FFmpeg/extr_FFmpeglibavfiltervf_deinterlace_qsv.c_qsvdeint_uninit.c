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
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {scalar_t__ nb_surface_ptrs; TYPE_1__* surface_ptrs; scalar_t__ nb_mem_ids; TYPE_1__* mem_ids; TYPE_1__* work_frames; int /*<<< orphan*/  hw_frames_ctx; int /*<<< orphan*/ * session; } ;
struct TYPE_6__ {int /*<<< orphan*/  frame; struct TYPE_6__* next; } ;
typedef  TYPE_1__ QSVFrame ;
typedef  TYPE_2__ QSVDeintContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  MFXClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

__attribute__((used)) static void qsvdeint_uninit(AVFilterContext *ctx)
{
    QSVDeintContext *s = ctx->priv;
    QSVFrame *cur;

    if (s->session) {
        MFXClose(s->session);
        s->session = NULL;
    }
    av_buffer_unref(&s->hw_frames_ctx);

    cur = s->work_frames;
    while (cur) {
        s->work_frames = cur->next;
        av_frame_free(&cur->frame);
        av_freep(&cur);
        cur = s->work_frames;
    }

    av_freep(&s->mem_ids);
    s->nb_mem_ids = 0;

    av_freep(&s->surface_ptrs);
    s->nb_surface_ptrs = 0;
}