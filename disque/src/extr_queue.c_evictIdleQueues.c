#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
typedef  int /*<<< orphan*/  queue ;
typedef  int mstime_t ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_2__ {int /*<<< orphan*/  queues; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 scalar_t__ GCQueue (int /*<<< orphan*/ *,int) ; 
 int QUEUE_MAX_IDLE_TIME ; 
 int /*<<< orphan*/ * dictGetRandomKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetVal (int /*<<< orphan*/ *) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 int getMemoryWarningLevel () ; 
 int mstime () ; 
 TYPE_1__ server ; 

int evictIdleQueues(void) {
    mstime_t start = mstime();
    time_t max_idle_time = QUEUE_MAX_IDLE_TIME;
    long sampled = 0, evicted = 0;

    if (getMemoryWarningLevel() > 0) max_idle_time /= 30;
    if (getMemoryWarningLevel() > 1) max_idle_time = 2;
    while (dictSize(server.queues) != 0) {
        dictEntry *de = dictGetRandomKey(server.queues);
        queue *q = dictGetVal(de);

        sampled++;
        if (GCQueue(q,max_idle_time) == C_OK) evicted++;

        /* First exit condition: we are able to expire less than 10% of
         * entries. */
        if (sampled > 10 && (evicted * 10) < sampled) break;

        /* Second exit condition: we are looping for some time and maybe
         * we are using more than one or two milliseconds of time. */
        if (((sampled+1) % 1000) == 0 && mstime()-start > 1) break;
    }
    return evicted;
}