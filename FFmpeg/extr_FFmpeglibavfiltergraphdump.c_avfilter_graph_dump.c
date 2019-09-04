#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  AVFilterGraph ;
typedef  TYPE_1__ AVBPrint ;

/* Variables and functions */
 scalar_t__ AV_BPRINT_SIZE_COUNT_ONLY ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_1__*,char**) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  avfilter_graph_dump_to_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 

char *avfilter_graph_dump(AVFilterGraph *graph, const char *options)
{
    AVBPrint buf;
    char *dump;

    av_bprint_init(&buf, 0, AV_BPRINT_SIZE_COUNT_ONLY);
    avfilter_graph_dump_to_buf(&buf, graph);
    av_bprint_init(&buf, buf.len + 1, buf.len + 1);
    avfilter_graph_dump_to_buf(&buf, graph);
    av_bprint_finalize(&buf, &dump);
    return dump;
}