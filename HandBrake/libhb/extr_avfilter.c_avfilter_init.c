#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hb_filter_private_s {int dummy; } ;
struct TYPE_6__ {int initialized; int /*<<< orphan*/ * graph; int /*<<< orphan*/  list; void* output; void* input; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_7__ {int /*<<< orphan*/  settings; TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;
typedef  void* hb_filter_init_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_avfilter_graph_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_avfilter_graph_init (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  hb_avfilter_graph_update_init (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  hb_buffer_list_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int avfilter_init( hb_filter_object_t * filter, hb_filter_init_t * init )
{
    hb_filter_private_t * pv = NULL;

    pv = calloc(1, sizeof(struct hb_filter_private_s));
    filter->private_data = pv;
    if (pv == NULL)
    {
        return 1;
    }
    pv->input = *init;
    pv->initialized = 1;

    pv->graph = hb_avfilter_graph_init(filter->settings, init);
    if (pv->graph == NULL)
    {
        goto fail;
    }

    // Retrieve the parameters of the output filter
    hb_avfilter_graph_update_init(pv->graph, init);
    pv->output = *init;

    hb_buffer_list_clear(&pv->list);

    return 0;

fail:
    hb_avfilter_graph_close(&pv->graph);
    free(pv);

    return 1;
}