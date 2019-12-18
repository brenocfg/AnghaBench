#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nb_outputs; } ;
struct TYPE_5__ {int nb_filters; TYPE_2__** filters; } ;
typedef  TYPE_1__ AVFilterGraph ;
typedef  TYPE_2__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVClass ;

/* Variables and functions */
 int avfilter_config_links (TYPE_2__*) ; 

__attribute__((used)) static int graph_config_links(AVFilterGraph *graph, AVClass *log_ctx)
{
    AVFilterContext *filt;
    int i, ret;

    for (i = 0; i < graph->nb_filters; i++) {
        filt = graph->filters[i];

        if (!filt->nb_outputs) {
            if ((ret = avfilter_config_links(filt)))
                return ret;
        }
    }

    return 0;
}