#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* src; } ;
struct TYPE_9__ {scalar_t__ single_pic; scalar_t__ outpicref; } ;
struct TYPE_8__ {TYPE_3__** inputs; TYPE_2__* priv; } ;
typedef  TYPE_2__ ShowWavesContext ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int ff_request_frame (TYPE_3__*) ; 
 int /*<<< orphan*/  push_frame (TYPE_3__*) ; 
 int /*<<< orphan*/  push_single_pic (TYPE_3__*) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    ShowWavesContext *showwaves = outlink->src->priv;
    AVFilterLink *inlink = outlink->src->inputs[0];
    int ret;

    ret = ff_request_frame(inlink);
    if (ret == AVERROR_EOF && showwaves->outpicref) {
        if (showwaves->single_pic)
            push_single_pic(outlink);
        else
            push_frame(outlink);
    }

    return ret;
}