#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mstime_t ;
struct TYPE_4__ {int gc_retry; } ;
typedef  TYPE_1__ job ;
struct TYPE_5__ {scalar_t__ mstime; } ;

/* Variables and functions */
 scalar_t__ JOB_GC_RETRY_MAX_PERIOD ; 
 int JOB_GC_RETRY_MIN_PERIOD ; 
 scalar_t__ randomTimeError (int) ; 
 TYPE_2__ server ; 

mstime_t getNextGCRetryTime(job *job) {
    mstime_t period = JOB_GC_RETRY_MIN_PERIOD * (1 << job->gc_retry);
    if (period > JOB_GC_RETRY_MAX_PERIOD) period = JOB_GC_RETRY_MAX_PERIOD;
    /* Desync a bit the GC process, it is a waste of resources for
     * multiple nodes to try to GC at the same time. */
    return server.mstime + period + randomTimeError(500);
}