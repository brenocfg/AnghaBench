#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int nb_outputs; TYPE_1__** outputs; } ;
struct TYPE_6__ {TYPE_2__* dst; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_1__ AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 unsigned int FF_INLINK_IDX (TYPE_1__*) ; 
 int /*<<< orphan*/ * ff_get_video_buffer (TYPE_1__*,int,int) ; 

__attribute__((used)) static AVFrame *get_video_buffer(AVFilterLink *inlink, int w, int h)
{
    AVFilterContext *ctx = inlink->dst;
    unsigned in_no = FF_INLINK_IDX(inlink);
    AVFilterLink *outlink = ctx->outputs[in_no % ctx->nb_outputs];

    return ff_get_video_buffer(outlink, w, h);
}