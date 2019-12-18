#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* command_queue; } ;
struct TYPE_11__ {int time; int /*<<< orphan*/  flags; int /*<<< orphan*/  arg; int /*<<< orphan*/  command; } ;
struct TYPE_10__ {TYPE_6__* dst; int /*<<< orphan*/  time_base; } ;
struct TYPE_9__ {int pts; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterCommand ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avfilter_process_command (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_command_queue_pop (TYPE_6__*) ; 

int ff_inlink_process_commands(AVFilterLink *link, const AVFrame *frame)
{
    AVFilterCommand *cmd = link->dst->command_queue;

    while(cmd && cmd->time <= frame->pts * av_q2d(link->time_base)){
        av_log(link->dst, AV_LOG_DEBUG,
               "Processing command time:%f command:%s arg:%s\n",
               cmd->time, cmd->command, cmd->arg);
        avfilter_process_command(link->dst, cmd->command, cmd->arg, 0, 0, cmd->flags);
        ff_command_queue_pop(link->dst);
        cmd= link->dst->command_queue;
    }
    return 0;
}