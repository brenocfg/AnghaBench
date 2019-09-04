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
struct TYPE_4__ {scalar_t__ nb_surface_ptrs_out; scalar_t__ nb_surface_ptrs_in; int /*<<< orphan*/  surface_ptrs_out; int /*<<< orphan*/  surface_ptrs_in; scalar_t__ nb_mem_ids_out; scalar_t__ nb_mem_ids_in; int /*<<< orphan*/  mem_ids_out; int /*<<< orphan*/  mem_ids_in; int /*<<< orphan*/ * session; } ;
typedef  TYPE_1__ QSVScaleContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  MFXClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qsvscale_uninit(AVFilterContext *ctx)
{
    QSVScaleContext *s = ctx->priv;

    if (s->session) {
        MFXClose(s->session);
        s->session = NULL;
    }

    av_freep(&s->mem_ids_in);
    av_freep(&s->mem_ids_out);
    s->nb_mem_ids_in  = 0;
    s->nb_mem_ids_out = 0;

    av_freep(&s->surface_ptrs_in);
    av_freep(&s->surface_ptrs_out);
    s->nb_surface_ptrs_in  = 0;
    s->nb_surface_ptrs_out = 0;
}