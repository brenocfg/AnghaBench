#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int pts; } ;
struct TYPE_12__ {int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_11__ {TYPE_4__* src; } ;
struct TYPE_10__ {scalar_t__ pts; } ;
struct TYPE_9__ {int eof; scalar_t__ cur_pts; TYPE_8__* second; } ;
typedef  TYPE_1__ NNEDIContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* av_frame_clone (TYPE_8__*) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int request_frame(AVFilterLink *link)
{
    AVFilterContext *ctx = link->src;
    NNEDIContext *s = ctx->priv;
    int ret;

    if (s->eof)
        return AVERROR_EOF;

    ret  = ff_request_frame(ctx->inputs[0]);

    if (ret == AVERROR_EOF && s->second) {
        AVFrame *next = av_frame_clone(s->second);

        if (!next)
            return AVERROR(ENOMEM);

        next->pts = s->second->pts * 2 - s->cur_pts;
        s->eof = 1;

        filter_frame(ctx->inputs[0], next);
    } else if (ret < 0) {
        return ret;
    }

    return 0;
}