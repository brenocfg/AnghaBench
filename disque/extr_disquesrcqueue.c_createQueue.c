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
typedef  int /*<<< orphan*/  robj ;
struct TYPE_6__ {int /*<<< orphan*/ * name; scalar_t__ jobs_out; scalar_t__ jobs_in; scalar_t__ prev_import_jobs_count; int /*<<< orphan*/  prev_import_jobs_time; scalar_t__ current_import_jobs_count; int /*<<< orphan*/  current_import_jobs_time; int /*<<< orphan*/ * clients; int /*<<< orphan*/ * needjobs_responders; scalar_t__ needjobs_adhoc_attempt; scalar_t__ needjobs_adhoc_time; scalar_t__ needjobs_bcast_attempt; scalar_t__ needjobs_bcast_time; int /*<<< orphan*/  atime; int /*<<< orphan*/  ctime; int /*<<< orphan*/  sl; scalar_t__ flags; } ;
typedef  TYPE_1__ queue ;
struct TYPE_7__ {int /*<<< orphan*/  queues; int /*<<< orphan*/  mstime; int /*<<< orphan*/  unixtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  skiplistCompareJobsInQueue ; 
 int /*<<< orphan*/  skiplistCreate (int /*<<< orphan*/ ) ; 
 TYPE_1__* zmalloc (int) ; 

queue *createQueue(robj *name) {
    if (dictFind(server.queues,name) != NULL) return NULL;

    queue *q = zmalloc(sizeof(queue));
    q->name = name;
    q->flags = 0;
    incrRefCount(name);
    q->sl = skiplistCreate(skiplistCompareJobsInQueue);
    q->ctime = server.unixtime;
    q->atime = server.unixtime;
    q->needjobs_bcast_time = 0;
    q->needjobs_bcast_attempt = 0;
    q->needjobs_adhoc_time = 0;
    q->needjobs_adhoc_attempt = 0;
    q->needjobs_responders = NULL; /* Created on demand to save memory. */
    q->clients = NULL; /* Created on demand to save memory. */

    q->current_import_jobs_time = server.mstime;
    q->current_import_jobs_count = 0;
    q->prev_import_jobs_time = server.mstime;
    q->prev_import_jobs_count = 0;
    q->jobs_in = 0;
    q->jobs_out = 0;

    incrRefCount(name); /* Another refernce in the hash table key. */
    dictAdd(server.queues,q->name,q);
    return q;
}