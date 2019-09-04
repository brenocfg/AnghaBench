#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_inputs; } ;
struct TYPE_8__ {int /*<<< orphan*/ * filters; scalar_t__ nb_filters; } ;
typedef  int /*<<< orphan*/  AVFilterInOut ;
typedef  TYPE_1__ AVFilterGraph ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  WHITESPACES ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  avfilter_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avfilter_inout_free (int /*<<< orphan*/ **) ; 
 int link_filter_inouts (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,void*) ; 
 int parse_filter (TYPE_2__**,char const**,TYPE_1__*,int,void*) ; 
 int parse_inputs (char const**,int /*<<< orphan*/ **,int /*<<< orphan*/ **,void*) ; 
 int parse_outputs (char const**,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,void*) ; 
 int parse_sws_flags (char const**,TYPE_1__*) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

int avfilter_graph_parse_ptr(AVFilterGraph *graph, const char *filters,
                         AVFilterInOut **open_inputs_ptr, AVFilterInOut **open_outputs_ptr,
                         void *log_ctx)
{
    int index = 0, ret = 0;
    char chr = 0;

    AVFilterInOut *curr_inputs = NULL;
    AVFilterInOut *open_inputs  = open_inputs_ptr  ? *open_inputs_ptr  : NULL;
    AVFilterInOut *open_outputs = open_outputs_ptr ? *open_outputs_ptr : NULL;

    if ((ret = parse_sws_flags(&filters, graph)) < 0)
        goto end;

    do {
        AVFilterContext *filter;
        const char *filterchain = filters;
        filters += strspn(filters, WHITESPACES);

        if ((ret = parse_inputs(&filters, &curr_inputs, &open_outputs, log_ctx)) < 0)
            goto end;

        if ((ret = parse_filter(&filter, &filters, graph, index, log_ctx)) < 0)
            goto end;

        if (filter->nb_inputs == 1 && !curr_inputs && !index) {
            /* First input pad, assume it is "[in]" if not specified */
            const char *tmp = "[in]";
            if ((ret = parse_inputs(&tmp, &curr_inputs, &open_outputs, log_ctx)) < 0)
                goto end;
        }

        if ((ret = link_filter_inouts(filter, &curr_inputs, &open_inputs, log_ctx)) < 0)
            goto end;

        if ((ret = parse_outputs(&filters, &curr_inputs, &open_inputs, &open_outputs,
                                 log_ctx)) < 0)
            goto end;

        filters += strspn(filters, WHITESPACES);
        chr = *filters++;

        if (chr == ';' && curr_inputs) {
            av_log(log_ctx, AV_LOG_ERROR,
                   "Invalid filterchain containing an unlabelled output pad: \"%s\"\n",
                   filterchain);
            ret = AVERROR(EINVAL);
            goto end;
        }
        index++;
    } while (chr == ',' || chr == ';');

    if (chr) {
        av_log(log_ctx, AV_LOG_ERROR,
               "Unable to parse graph description substring: \"%s\"\n",
               filters - 1);
        ret = AVERROR(EINVAL);
        goto end;
    }

    if (curr_inputs) {
        /* Last output pad, assume it is "[out]" if not specified */
        const char *tmp = "[out]";
        if ((ret = parse_outputs(&tmp, &curr_inputs, &open_inputs, &open_outputs,
                                 log_ctx)) < 0)
            goto end;
    }

end:
    /* clear open_in/outputs only if not passed as parameters */
    if (open_inputs_ptr) *open_inputs_ptr = open_inputs;
    else avfilter_inout_free(&open_inputs);
    if (open_outputs_ptr) *open_outputs_ptr = open_outputs;
    else avfilter_inout_free(&open_outputs);
    avfilter_inout_free(&curr_inputs);

    if (ret < 0) {
        while (graph->nb_filters)
            avfilter_free(graph->filters[0]);
        av_freep(&graph->filters);
    }
    return ret;
}