#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVFilterGraph ;

/* Variables and functions */
 int graph_check_links (int /*<<< orphan*/ *,void*) ; 
 int graph_check_validity (int /*<<< orphan*/ *,void*) ; 
 int graph_config_formats (int /*<<< orphan*/ *,void*) ; 
 int graph_config_links (int /*<<< orphan*/ *,void*) ; 
 int graph_config_pointers (int /*<<< orphan*/ *,void*) ; 
 int graph_insert_fifos (int /*<<< orphan*/ *,void*) ; 

int avfilter_graph_config(AVFilterGraph *graphctx, void *log_ctx)
{
    int ret;

    if ((ret = graph_check_validity(graphctx, log_ctx)))
        return ret;
    if ((ret = graph_insert_fifos(graphctx, log_ctx)) < 0)
        return ret;
    if ((ret = graph_config_formats(graphctx, log_ctx)))
        return ret;
    if ((ret = graph_config_links(graphctx, log_ctx)))
        return ret;
    if ((ret = graph_check_links(graphctx, log_ctx)))
        return ret;
    if ((ret = graph_config_pointers(graphctx, log_ctx)))
        return ret;

    return 0;
}