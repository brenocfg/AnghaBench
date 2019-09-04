#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nb_outputs; int nb_inputs; int /*<<< orphan*/  graph; TYPE_1__** inputs; TYPE_2__** outputs; } ;
struct TYPE_6__ {int /*<<< orphan*/ * filter; } ;
struct TYPE_5__ {int /*<<< orphan*/ * filter; } ;
typedef  TYPE_3__ FilterGraph ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  avfilter_graph_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_filtergraph(FilterGraph *fg)
{
    int i;
    for (i = 0; i < fg->nb_outputs; i++)
        fg->outputs[i]->filter = (AVFilterContext *)NULL;
    for (i = 0; i < fg->nb_inputs; i++)
        fg->inputs[i]->filter = (AVFilterContext *)NULL;
    avfilter_graph_free(&fg->graph);
}