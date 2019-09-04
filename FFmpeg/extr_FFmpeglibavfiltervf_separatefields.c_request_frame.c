#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int pts; int /*<<< orphan*/  top_field_first; } ;
struct TYPE_10__ {int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_9__ {TYPE_3__* src; } ;
struct TYPE_8__ {TYPE_6__* second; int /*<<< orphan*/  nb_planes; } ;
typedef  TYPE_1__ SeparateFieldsContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  extract_field (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_2__*,TYPE_6__*) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    SeparateFieldsContext *s = ctx->priv;
    int ret;

    ret = ff_request_frame(ctx->inputs[0]);
    if (ret == AVERROR_EOF && s->second) {
        s->second->pts *= 2;
        extract_field(s->second, s->nb_planes, s->second->top_field_first);
        ret = ff_filter_frame(outlink, s->second);
        s->second = 0;
    }

    return ret;
}