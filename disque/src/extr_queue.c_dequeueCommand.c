#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ state; } ;
typedef  TYPE_1__ job ;
struct TYPE_10__ {int argc; TYPE_4__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_11__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 scalar_t__ C_OK ; 
 scalar_t__ JOB_STATE_QUEUED ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,int) ; 
 scalar_t__ dequeueJob (TYPE_1__*) ; 
 TYPE_1__* lookupJob (int /*<<< orphan*/ ) ; 
 scalar_t__ validateJobIDs (TYPE_2__*,TYPE_4__**,int) ; 

void dequeueCommand(client *c) {
    int j, dequeued = 0;

    if (validateJobIDs(c,c->argv+1,c->argc-1) == C_ERR) return;

    /* Enqueue all the jobs in active state. */
    for (j = 1; j < c->argc; j++) {
        job *job = lookupJob(c->argv[j]->ptr);
        if (job == NULL) continue;

        if (job->state == JOB_STATE_QUEUED && dequeueJob(job) == C_OK)
            dequeued++;
    }
    addReplyLongLong(c,dequeued);
}