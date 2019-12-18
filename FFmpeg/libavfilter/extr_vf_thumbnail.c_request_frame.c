#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ n; } ;
typedef  TYPE_1__ ThumbContext ;
struct TYPE_9__ {int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_8__ {TYPE_3__* src; } ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int ff_filter_frame (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_best_frame (TYPE_3__*) ; 

__attribute__((used)) static int request_frame(AVFilterLink *link)
{
    AVFilterContext *ctx = link->src;
    ThumbContext *s = ctx->priv;
    int ret = ff_request_frame(ctx->inputs[0]);

    if (ret == AVERROR_EOF && s->n) {
        ret = ff_filter_frame(link, get_best_frame(ctx));
        if (ret < 0)
            return ret;
        ret = AVERROR_EOF;
    }
    if (ret < 0)
        return ret;
    return 0;
}