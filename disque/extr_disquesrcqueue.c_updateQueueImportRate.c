#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int current_import_jobs_time; int prev_import_jobs_time; scalar_t__ current_import_jobs_count; scalar_t__ prev_import_jobs_count; } ;
typedef  TYPE_1__ queue ;
struct TYPE_5__ {int mstime; } ;

/* Variables and functions */
 TYPE_3__ server ; 

void updateQueueImportRate(queue *q) {
    /* If the current second no longer matches the current counter
     * timestamp, copy the old timestamp/counter into 'prev', and
     * start a new counter with an updated time. */
    if (server.mstime - q->current_import_jobs_time > 1000) {
        q->prev_import_jobs_time = q->current_import_jobs_time;
        q->prev_import_jobs_count = q->current_import_jobs_count;
        q->current_import_jobs_time = server.mstime;
        q->current_import_jobs_count = 0;
    }
    /* Anyway, update the current counter. */
    q->current_import_jobs_count++;
}