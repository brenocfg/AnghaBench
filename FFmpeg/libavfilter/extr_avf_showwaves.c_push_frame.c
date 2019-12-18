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
struct TYPE_8__ {TYPE_1__* priv; TYPE_2__** inputs; } ;
struct TYPE_7__ {int channels; TYPE_3__* src; } ;
struct TYPE_6__ {scalar_t__* buf_idy; scalar_t__ buf_idx; int /*<<< orphan*/ * outpicref; } ;
typedef  TYPE_1__ ShowWavesContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int ff_filter_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) inline static int push_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    AVFilterLink *inlink = ctx->inputs[0];
    ShowWavesContext *showwaves = outlink->src->priv;
    int nb_channels = inlink->channels;
    int ret, i;

    ret = ff_filter_frame(outlink, showwaves->outpicref);
    showwaves->outpicref = NULL;
    showwaves->buf_idx = 0;
    for (i = 0; i < nb_channels; i++)
        showwaves->buf_idy[i] = 0;
    return ret;
}