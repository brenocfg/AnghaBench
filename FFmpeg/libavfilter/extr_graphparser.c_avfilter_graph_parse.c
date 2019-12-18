#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* filter; } ;
struct TYPE_17__ {int /*<<< orphan*/ * filters; scalar_t__ nb_filters; } ;
struct TYPE_16__ {int /*<<< orphan*/  pad_idx; TYPE_6__* filter_ctx; void* name; struct TYPE_16__* next; } ;
struct TYPE_15__ {char const* name; } ;
typedef  TYPE_2__ AVFilterInOut ;
typedef  TYPE_3__ AVFilterGraph ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*) ; 
 void* av_strdup (char*) ; 
 int /*<<< orphan*/  avfilter_free (int /*<<< orphan*/ ) ; 
 int avfilter_graph_parse2 (TYPE_3__*,char const*,TYPE_2__**,TYPE_2__**) ; 
 int /*<<< orphan*/  avfilter_inout_free (TYPE_2__**) ; 
 int avfilter_link (TYPE_6__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* extract_inout (void*,TYPE_2__**) ; 

int avfilter_graph_parse(AVFilterGraph *graph, const char *filters,
                         AVFilterInOut *open_inputs,
                         AVFilterInOut *open_outputs, void *log_ctx)
{
    int ret;
    AVFilterInOut *cur, *match, *inputs = NULL, *outputs = NULL;

    if ((ret = avfilter_graph_parse2(graph, filters, &inputs, &outputs)) < 0)
        goto fail;

    /* First input can be omitted if it is "[in]" */
    if (inputs && !inputs->name)
        inputs->name = av_strdup("in");
    for (cur = inputs; cur; cur = cur->next) {
        if (!cur->name) {
              av_log(log_ctx, AV_LOG_ERROR,
                     "Not enough inputs specified for the \"%s\" filter.\n",
                     cur->filter_ctx->filter->name);
              ret = AVERROR(EINVAL);
              goto fail;
        }
        if (!(match = extract_inout(cur->name, &open_outputs)))
            continue;
        ret = avfilter_link(match->filter_ctx, match->pad_idx,
                            cur->filter_ctx,   cur->pad_idx);
        avfilter_inout_free(&match);
        if (ret < 0)
            goto fail;
    }

    /* Last output can be omitted if it is "[out]" */
    if (outputs && !outputs->name)
        outputs->name = av_strdup("out");
    for (cur = outputs; cur; cur = cur->next) {
        if (!cur->name) {
            av_log(log_ctx, AV_LOG_ERROR,
                   "Invalid filterchain containing an unlabelled output pad: \"%s\"\n",
                   filters);
            ret = AVERROR(EINVAL);
            goto fail;
        }
        if (!(match = extract_inout(cur->name, &open_inputs)))
            continue;
        ret = avfilter_link(cur->filter_ctx,   cur->pad_idx,
                            match->filter_ctx, match->pad_idx);
        avfilter_inout_free(&match);
        if (ret < 0)
            goto fail;
    }

 fail:
    if (ret < 0) {
        while (graph->nb_filters)
            avfilter_free(graph->filters[0]);
        av_freep(&graph->filters);
    }
    avfilter_inout_free(&inputs);
    avfilter_inout_free(&outputs);
    avfilter_inout_free(&open_inputs);
    avfilter_inout_free(&open_outputs);
    return ret;
}