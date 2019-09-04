#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void aeEventLoop ;
struct TYPE_13__ {TYPE_6__* obj; TYPE_1__* level; } ;
typedef  TYPE_5__ skiplistNode ;
typedef  scalar_t__ mstime_t ;
struct TYPE_14__ {scalar_t__ awakeme; } ;
typedef  TYPE_6__ job ;
struct TYPE_15__ {int mstime; TYPE_4__* awakeme; } ;
struct TYPE_12__ {TYPE_3__* header; } ;
struct TYPE_11__ {TYPE_2__* level; } ;
struct TYPE_10__ {TYPE_5__* forward; } ;
struct TYPE_9__ {TYPE_5__* forward; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  latencyAddSampleIfNeeded (char*,scalar_t__) ; 
 int /*<<< orphan*/  latencyEndMonitor (scalar_t__) ; 
 int /*<<< orphan*/  latencyStartMonitor (scalar_t__) ; 
 scalar_t__ mstime () ; 
 int /*<<< orphan*/  processJob (TYPE_6__*) ; 
 TYPE_7__ server ; 

int processJobs(struct aeEventLoop *eventLoop, long long id, void *clientData) {
    int period = 100; /* 100 ms default period. */
    int max = 10000; /* 10k jobs * 1000 milliseconds = 10M jobs/sec max. */
    mstime_t now = mstime(), latency;
    skiplistNode *current, *next;
    UNUSED(eventLoop);
    UNUSED(id);
    UNUSED(clientData);

#ifdef DEBUG_SCHEDULER
    static time_t last_log = 0;
    int canlog = 0;
    if (server.port == 25000 && time(NULL) != last_log) {
        last_log = time(NULL);
        canlog = 1;
    }

    if (canlog) printf("--- LEN: %d ---\n",
        (int) skiplistLength(server.awakeme));
#endif

    latencyStartMonitor(latency);
    server.mstime = now; /* Update it since it's used by processJob(). */
    current = server.awakeme->header->level[0].forward;
    while(current && max--) {
        job *j = current->obj;

#ifdef DEBUG_SCHEDULER
        if (canlog) {
            printf("%.*s %d (in %d) [%s]\n",
                JOB_ID_LEN, j->id,
                (int) j->awakeme,
                (int) (j->awakeme-server.mstime),
                jobStateToString(j->state));
        }
#endif

        if (j->awakeme > now) break;
        next = current->level[0].forward;
        processJob(j);
        current = next;
    }

    /* Try to block between 1 and 100 millseconds depending on how near
     * in time is the next async event to process. Note that because of
     * received commands or change in state jobs state may be modified so
     * we set a max time of 100 milliseconds to wakeup anyway. */
    current = server.awakeme->header->level[0].forward;
    if (current) {
        job *j = current->obj;
        period = server.mstime-j->awakeme;
        if (period < 1) period = 1;
        else if (period > 100) period = 100;
    }
    latencyEndMonitor(latency);
    latencyAddSampleIfNeeded("jobs-processing",latency);
#ifdef DEBUG_SCHEDULER
    if (canlog) printf("---\n\n");
#endif
    return period;
}