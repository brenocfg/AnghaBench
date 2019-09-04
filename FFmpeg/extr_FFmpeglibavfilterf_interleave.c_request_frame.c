#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  status_out; } ;
struct TYPE_11__ {int nb_inputs; TYPE_7__** inputs; TYPE_2__* priv; } ;
struct TYPE_10__ {TYPE_4__* src; } ;
struct TYPE_9__ {TYPE_1__* queues; } ;
struct TYPE_8__ {int /*<<< orphan*/  available; } ;
typedef  TYPE_2__ InterleaveContext ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int ff_request_frame (TYPE_7__*) ; 
 int push_frame (TYPE_4__*) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    InterleaveContext *s = ctx->priv;
    int i, ret;

    for (i = 0; i < ctx->nb_inputs; i++) {
        if (!s->queues[i].available && !ctx->inputs[i]->status_out) {
            ret = ff_request_frame(ctx->inputs[i]);
            if (ret != AVERROR_EOF)
                return ret;
        }
    }

    return push_frame(ctx);
}