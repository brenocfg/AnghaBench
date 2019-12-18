#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  job ;
struct TYPE_6__ {int argc; TYPE_3__** argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_1__*,int) ; 
 int /*<<< orphan*/  freeJob (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupJob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregisterJob (int /*<<< orphan*/ *) ; 
 scalar_t__ validateJobIDs (TYPE_1__*,TYPE_3__**,int) ; 

void deljobCommand(client *c) {
    int j, evicted = 0;

    if (validateJobIDs(c,c->argv+1,c->argc-1) == C_ERR) return;

    /* Perform the appropriate action for each job. */
    for (j = 1; j < c->argc; j++) {
        job *job = lookupJob(c->argv[j]->ptr);
        if (job == NULL) continue;
        unregisterJob(job);
        freeJob(job);
        evicted++;
    }
    addReplyLongLong(c,evicted);
}