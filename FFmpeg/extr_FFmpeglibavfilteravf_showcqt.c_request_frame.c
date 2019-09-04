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
struct TYPE_7__ {TYPE_1__* src; } ;
struct TYPE_6__ {TYPE_2__** inputs; } ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int ff_request_frame (TYPE_2__*) ; 
 int filter_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterLink *inlink = outlink->src->inputs[0];
    int ret;

    ret = ff_request_frame(inlink);
    if (ret == AVERROR_EOF)
        ret = filter_frame(inlink, NULL);
    return ret;
}