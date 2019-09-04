#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int nb_inputs; int nb_outputs; TYPE_1__* filter; } ;
struct TYPE_16__ {int pad_idx; TYPE_3__* filter_ctx; struct TYPE_16__* name; struct TYPE_16__* next; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ AVFilterInOut ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  append_inout (TYPE_2__**,TYPE_2__**) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* av_mallocz (int) ; 
 int /*<<< orphan*/  insert_inout (TYPE_2__**,TYPE_2__*) ; 
 int link_filter (TYPE_3__*,int,TYPE_3__*,int,void*) ; 

__attribute__((used)) static int link_filter_inouts(AVFilterContext *filt_ctx,
                              AVFilterInOut **curr_inputs,
                              AVFilterInOut **open_inputs, void *log_ctx)
{
    int pad, ret;

    for (pad = 0; pad < filt_ctx->nb_inputs; pad++) {
        AVFilterInOut *p = *curr_inputs;

        if (p) {
            *curr_inputs = (*curr_inputs)->next;
            p->next = NULL;
        } else if (!(p = av_mallocz(sizeof(*p))))
            return AVERROR(ENOMEM);

        if (p->filter_ctx) {
            ret = link_filter(p->filter_ctx, p->pad_idx, filt_ctx, pad, log_ctx);
            av_freep(&p->name);
            av_freep(&p);
            if (ret < 0)
                return ret;
        } else {
            p->filter_ctx = filt_ctx;
            p->pad_idx = pad;
            append_inout(open_inputs, &p);
        }
    }

    if (*curr_inputs) {
        av_log(log_ctx, AV_LOG_ERROR,
               "Too many inputs specified for the \"%s\" filter.\n",
               filt_ctx->filter->name);
        return AVERROR(EINVAL);
    }

    pad = filt_ctx->nb_outputs;
    while (pad--) {
        AVFilterInOut *currlinkn = av_mallocz(sizeof(AVFilterInOut));
        if (!currlinkn)
            return AVERROR(ENOMEM);
        currlinkn->filter_ctx  = filt_ctx;
        currlinkn->pad_idx = pad;
        insert_inout(curr_inputs, currlinkn);
    }

    return 0;
}