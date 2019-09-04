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
struct TYPE_9__ {scalar_t__ more_data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * inputs; TYPE_3__* priv; } ;
struct TYPE_7__ {TYPE_2__* src; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_1__ AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;
typedef  TYPE_3__ AResampleContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int ff_filter_frame (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 scalar_t__ flush_frame (TYPE_1__*,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    AResampleContext *aresample = ctx->priv;
    int ret;

    // First try to get data from the internal buffers
    if (aresample->more_data) {
        AVFrame *outsamplesref;

        if (flush_frame(outlink, 0, &outsamplesref) >= 0) {
            return ff_filter_frame(outlink, outsamplesref);
        }
    }
    aresample->more_data = 0;

    // Second request more data from the input
    ret = ff_request_frame(ctx->inputs[0]);

    // Third if we hit the end flush
    if (ret == AVERROR_EOF) {
        AVFrame *outsamplesref;

        if ((ret = flush_frame(outlink, 1, &outsamplesref)) < 0)
            return ret;

        return ff_filter_frame(outlink, outsamplesref);
    }
    return ret;
}