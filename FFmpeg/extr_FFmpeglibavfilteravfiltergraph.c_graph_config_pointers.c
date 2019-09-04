#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int nb_inputs; unsigned int nb_outputs; TYPE_2__** inputs; TYPE_1__** outputs; } ;
struct TYPE_9__ {unsigned int nb_filters; int sink_links_count; TYPE_2__** sink_links; TYPE_4__** filters; } ;
struct TYPE_8__ {int age_index; TYPE_3__* graph; } ;
struct TYPE_7__ {int age_index; TYPE_3__* graph; } ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterGraph ;
typedef  TYPE_4__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVClass ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_2__** av_calloc (int,int) ; 

__attribute__((used)) static int graph_config_pointers(AVFilterGraph *graph,
                                             AVClass *log_ctx)
{
    unsigned i, j;
    int sink_links_count = 0, n = 0;
    AVFilterContext *f;
    AVFilterLink **sinks;

    for (i = 0; i < graph->nb_filters; i++) {
        f = graph->filters[i];
        for (j = 0; j < f->nb_inputs; j++) {
            f->inputs[j]->graph     = graph;
            f->inputs[j]->age_index = -1;
        }
        for (j = 0; j < f->nb_outputs; j++) {
            f->outputs[j]->graph    = graph;
            f->outputs[j]->age_index= -1;
        }
        if (!f->nb_outputs) {
            if (f->nb_inputs > INT_MAX - sink_links_count)
                return AVERROR(EINVAL);
            sink_links_count += f->nb_inputs;
        }
    }
    sinks = av_calloc(sink_links_count, sizeof(*sinks));
    if (!sinks)
        return AVERROR(ENOMEM);
    for (i = 0; i < graph->nb_filters; i++) {
        f = graph->filters[i];
        if (!f->nb_outputs) {
            for (j = 0; j < f->nb_inputs; j++) {
                sinks[n] = f->inputs[j];
                f->inputs[j]->age_index = n++;
            }
        }
    }
    av_assert0(n == sink_links_count);
    graph->sink_links       = sinks;
    graph->sink_links_count = sink_links_count;
    return 0;
}