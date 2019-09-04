#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* cmd; int /*<<< orphan*/  argc; int /*<<< orphan*/  argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_9__ {int /*<<< orphan*/  stat_numcommands; int /*<<< orphan*/  monitors; int /*<<< orphan*/  loading; } ;
struct TYPE_7__ {int flags; long long microseconds; int /*<<< orphan*/  calls; int /*<<< orphan*/  (* proc ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int CMD_CALL_SLOWLOG ; 
 int CMD_CALL_STATS ; 
 int CMD_FAST ; 
 int CMD_SKIP_MONITOR ; 
 int /*<<< orphan*/  latencyAddSampleIfNeeded (char*,long long) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replicationFeedMonitors (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  slowlogPushEntryIfNeeded (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 long long ustime () ; 

void call(client *c, int flags) {
    long long start, duration;

    /* Sent the command to clients in MONITOR mode, only if the commands are
     * not generated from reading an AOF. */
    if (listLength(server.monitors) &&
        !server.loading &&
        !(c->cmd->flags & CMD_SKIP_MONITOR))
    {
        replicationFeedMonitors(c,server.monitors,c->argv,c->argc);
    }

    /* Call the command. */
    start = ustime();
    c->cmd->proc(c);
    duration = ustime()-start;

    /* Log the command into the Slow log if needed, and populate the
     * per-command statistics that we show in INFO commandstats. */
    if (flags & CMD_CALL_SLOWLOG) {
        char *latency_event = (c->cmd->flags & CMD_FAST) ?
                              "fast-command" : "command";
        latencyAddSampleIfNeeded(latency_event,duration/1000);
        slowlogPushEntryIfNeeded(c->argv,c->argc,duration);
    }
    if (flags & CMD_CALL_STATS) {
        c->cmd->microseconds += duration;
        c->cmd->calls++;
    }
    server.stat_numcommands++;
}