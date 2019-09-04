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
struct TYPE_10__ {double time; int flags; struct TYPE_10__* next; void* arg; void* command; } ;
struct TYPE_9__ {char* name; TYPE_4__* command_queue; TYPE_1__* filter; } ;
struct TYPE_8__ {int nb_filters; TYPE_3__** filters; } ;
struct TYPE_7__ {char* name; } ;
typedef  TYPE_2__ AVFilterGraph ;
typedef  TYPE_3__ AVFilterContext ;
typedef  TYPE_4__ AVFilterCommand ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVFILTER_CMD_FLAG_ONE ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_4__* av_mallocz (int) ; 
 void* av_strdup (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int avfilter_graph_queue_command(AVFilterGraph *graph, const char *target, const char *command, const char *arg, int flags, double ts)
{
    int i;

    if(!graph)
        return 0;

    for (i = 0; i < graph->nb_filters; i++) {
        AVFilterContext *filter = graph->filters[i];
        if(filter && (!strcmp(target, "all") || !strcmp(target, filter->name) || !strcmp(target, filter->filter->name))){
            AVFilterCommand **queue = &filter->command_queue, *next;
            while (*queue && (*queue)->time <= ts)
                queue = &(*queue)->next;
            next = *queue;
            *queue = av_mallocz(sizeof(AVFilterCommand));
            if (!*queue)
                return AVERROR(ENOMEM);

            (*queue)->command = av_strdup(command);
            (*queue)->arg     = av_strdup(arg);
            (*queue)->time    = ts;
            (*queue)->flags   = flags;
            (*queue)->next    = next;
            if(flags & AVFILTER_CMD_FLAG_ONE)
                return 0;
        }
    }

    return 0;
}