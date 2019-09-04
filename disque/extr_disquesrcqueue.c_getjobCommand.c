#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {char* ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_22__ {int flags; } ;
typedef  TYPE_2__ queue ;
typedef  int /*<<< orphan*/  mstime_t ;
typedef  int /*<<< orphan*/  job ;
struct TYPE_23__ {int argc; TYPE_1__** argv; } ;
typedef  TYPE_3__ client ;
struct TYPE_24__ {int /*<<< orphan*/  leavingerr; int /*<<< orphan*/  nullmultibulk; int /*<<< orphan*/  syntaxerr; } ;

/* Variables and functions */
 int C_OK ; 
 int /*<<< orphan*/  GETJOB_FLAG_NONE ; 
 int /*<<< orphan*/  GETJOB_FLAG_WITHCOUNTERS ; 
 int /*<<< orphan*/  NEEDJOBS_CLIENTS_WAITING ; 
 int /*<<< orphan*/  NEEDJOBS_REACHED_ZERO ; 
 int QUEUE_FLAG_PAUSED_OUT ; 
 int /*<<< orphan*/  UNIT_MILLISECONDS ; 
 void* addDeferredMultiBulkLength (TYPE_3__*) ; 
 int /*<<< orphan*/  addReply (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  addReplyJob (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blockForJobs (TYPE_3__*,TYPE_1__**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getLongLongFromObject (TYPE_1__*,long long*) ; 
 int getTimeoutFromObjectOrReply (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* lookupQueue (TYPE_1__*) ; 
 scalar_t__ myselfLeaving () ; 
 int /*<<< orphan*/  needJobsForQueue (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  needJobsForQueueName (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * queueFetchJob (TYPE_2__*,unsigned long*) ; 
 int /*<<< orphan*/  setDeferredMultiBulkLength (TYPE_3__*,void*,long long) ; 
 TYPE_4__ shared ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

void getjobCommand(client *c) {
    mstime_t timeout = 0; /* Block forever by default. */
    long long count = 1, emitted_jobs = 0;
    int nohang = 0; /* Don't block even if all the queues are empty. */
    int withcounters = 0; /* Also return NACKs and deliveries counters. */
    robj **queues = NULL;
    int j, numqueues = 0;

    /* Parse args. */
    for (j = 1; j < c->argc; j++) {
        char *opt = c->argv[j]->ptr;
        int lastarg = j == c->argc-1;
        if (!strcasecmp(opt,"nohang")) {
            nohang = 1;
        } else if (!strcasecmp(opt,"withcounters")) {
            withcounters = 1;
        } else if (!strcasecmp(opt,"timeout") && !lastarg) {
            if (getTimeoutFromObjectOrReply(c,c->argv[j+1],&timeout,
                UNIT_MILLISECONDS) != C_OK) return;
            j++;
        } else if (!strcasecmp(opt,"count") && !lastarg) {
            int retval = getLongLongFromObject(c->argv[j+1],&count);
            if (retval != C_OK || count <= 0) {
                addReplyError(c,"COUNT must be a number greater than zero");
                return;
            }
            j++;
        } else if (!strcasecmp(opt,"from")) {
            queues = c->argv+j+1;
            numqueues = c->argc - j - 1;
            break; /* Don't process options after this. */
        } else {
            addReply(c,shared.syntaxerr);
            return;
        }
    }

    /* FROM is mandatory. */
    if (queues == NULL || numqueues == 0) {
        addReply(c,shared.syntaxerr);
        return;
    }

    /* First: try to avoid blocking if there is at least one job in at
     * least one queue. */
    void *mbulk = NULL;

    while(1) {
        long old_emitted = emitted_jobs;
        for (j = 0; j < numqueues; j++) {
            unsigned long qlen;
            queue *q = lookupQueue(queues[j]);
            job *job = NULL;
            if (q && !(q->flags & QUEUE_FLAG_PAUSED_OUT))
                job = queueFetchJob(q,&qlen);

            if (!job) {
                if (!q)
                    needJobsForQueueName(queues[j],NEEDJOBS_CLIENTS_WAITING);
                else
                    needJobsForQueue(q,NEEDJOBS_CLIENTS_WAITING);
                continue;
            } else if (job && qlen == 0) {
                needJobsForQueue(q,NEEDJOBS_REACHED_ZERO);
            }
            if (!mbulk) mbulk = addDeferredMultiBulkLength(c);
            addReplyJob(c,job,withcounters ? GETJOB_FLAG_WITHCOUNTERS :
                                             GETJOB_FLAG_NONE);
            count--;
            emitted_jobs++;
            if (count == 0) break;
        }
        /* When we reached count or when we are no longer making
         * progresses (no jobs left in our queues), stop. */
        if (count == 0 || old_emitted == emitted_jobs) break;
    }

    if (mbulk) {
        setDeferredMultiBulkLength(c,mbulk,emitted_jobs);
        return;
    }

    /* If NOHANG was given and there are no jobs, return NULL. */
    if (nohang) {
        addReply(c,shared.nullmultibulk);
        return;
    }

    /* If this node is leaving the cluster, we can't block waiting for
     * jobs: this would trigger the federation with other nodes in order
     * to import jobs here. Just return a -LEAVING error. */
    if (myselfLeaving()) {
        addReply(c,shared.leavingerr);
        return;
    }

    /* If we reached this point, we need to block. */
    blockForJobs(c,queues,numqueues,timeout,
            withcounters ? GETJOB_FLAG_WITHCOUNTERS : GETJOB_FLAG_NONE);
}