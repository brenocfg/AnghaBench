#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* name; TYPE_1__* filter; } ;
struct TYPE_7__ {int nb_filters; TYPE_3__** filters; } ;
struct TYPE_6__ {char* name; } ;
typedef  TYPE_2__ AVFilterGraph ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVFILTER_CMD_FLAG_FAST ; 
 int AVFILTER_CMD_FLAG_ONE ; 
 int /*<<< orphan*/  ENOSYS ; 
 int avfilter_process_command (TYPE_3__*,char const*,char const*,char*,int,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int avfilter_graph_send_command(AVFilterGraph *graph, const char *target, const char *cmd, const char *arg, char *res, int res_len, int flags)
{
    int i, r = AVERROR(ENOSYS);

    if (!graph)
        return r;

    if ((flags & AVFILTER_CMD_FLAG_ONE) && !(flags & AVFILTER_CMD_FLAG_FAST)) {
        r = avfilter_graph_send_command(graph, target, cmd, arg, res, res_len, flags | AVFILTER_CMD_FLAG_FAST);
        if (r != AVERROR(ENOSYS))
            return r;
    }

    if (res_len && res)
        res[0] = 0;

    for (i = 0; i < graph->nb_filters; i++) {
        AVFilterContext *filter = graph->filters[i];
        if (!strcmp(target, "all") || (filter->name && !strcmp(target, filter->name)) || !strcmp(target, filter->filter->name)) {
            r = avfilter_process_command(filter, cmd, arg, res, res_len, flags);
            if (r != AVERROR(ENOSYS)) {
                if ((flags & AVFILTER_CMD_FLAG_ONE) || r < 0)
                    return r;
            }
        }
    }

    return r;
}