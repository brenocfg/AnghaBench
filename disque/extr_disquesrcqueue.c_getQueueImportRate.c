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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {double prev_import_jobs_time; double current_import_jobs_count; scalar_t__ current_import_jobs_time; scalar_t__ prev_import_jobs_count; } ;
typedef  TYPE_1__ queue ;
struct TYPE_5__ {double mstime; } ;

/* Variables and functions */
 scalar_t__ IMPORT_RATE_WINDOW ; 
 int /*<<< orphan*/  ceil (double) ; 
 TYPE_2__ server ; 

uint32_t getQueueImportRate(queue *q) {
    double elapsed = server.mstime - q->prev_import_jobs_time;
    double messages = (double)q->prev_import_jobs_count +
                              q->current_import_jobs_count;

    /* If we did not received any message in the latest few seconds,
     * consider the import rate zero. */
    if ((server.mstime - q->current_import_jobs_time) > IMPORT_RATE_WINDOW)
        return 0;

    /* Min interval is 50 ms in order to never overestimate. */
    if (elapsed < 50) elapsed = 50;

    return ceil((double)messages*1000/elapsed);
}