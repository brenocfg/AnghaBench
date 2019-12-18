#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_15__ ;
typedef  struct TYPE_35__   TYPE_13__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_39__ {int flags; } ;
typedef  TYPE_3__ queue ;
typedef  int /*<<< orphan*/  mstime_t ;
struct TYPE_40__ {long long repl; int ctime; long long delay; long long retry; int /*<<< orphan*/  nodes_delivered; int /*<<< orphan*/  state; int /*<<< orphan*/  nodes_confirmed; scalar_t__ qtime; int /*<<< orphan*/  body; scalar_t__ etime; TYPE_15__* queue; } ;
typedef  TYPE_4__ job ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  clusterNode ;
struct TYPE_37__ {int added_node_time; TYPE_4__* job; int /*<<< orphan*/  timeout; } ;
struct TYPE_41__ {int argc; TYPE_1__ bpop; TYPE_15__** argv; } ;
typedef  TYPE_5__ client ;
struct TYPE_42__ {int /*<<< orphan*/  syntaxerr; } ;
struct TYPE_38__ {int size; int reachable_nodes_count; } ;
struct TYPE_36__ {char* ptr; } ;
struct TYPE_35__ {int /*<<< orphan*/  name; } ;
struct TYPE_34__ {scalar_t__ mstime; scalar_t__ unixtime; TYPE_2__* cluster; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOFLoadJob (TYPE_4__*) ; 
 int /*<<< orphan*/  BLOCKED_JOB_REPL ; 
 scalar_t__ C_ERR ; 
 int C_OK ; 
 long long JOB_DEFAULT_RETRY_MAX ; 
 int /*<<< orphan*/  JOB_STATE_ACTIVE ; 
 int /*<<< orphan*/  JOB_STATE_WAIT_REPL ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int QUEUE_FLAG_PAUSED_IN ; 
 int /*<<< orphan*/  UNIT_MILLISECONDS ; 
 int /*<<< orphan*/  addReply (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  addReplyJobID (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  addReplySds (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blockClient (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterNodesDictType ; 
 int /*<<< orphan*/  clusterReplicateJob (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  clusterSendEnqueue (int /*<<< orphan*/ *,TYPE_4__*,long long) ; 
 TYPE_4__* createJob (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long long,long long) ; 
 int /*<<< orphan*/  dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_13__*) ; 
 int /*<<< orphan*/  dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetRandomKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enqueueJob (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeJob (TYPE_4__*) ; 
 int getLongLongFromObject (TYPE_15__*,long long*) ; 
 scalar_t__ getMemoryWarningLevel () ; 
 int getTimeoutFromObjectOrReply (TYPE_5__*,TYPE_15__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  incrRefCount (TYPE_15__*) ; 
 TYPE_3__* lookupQueue (TYPE_15__*) ; 
 int mstime () ; 
 TYPE_13__* myself ; 
 int myselfLeaving () ; 
 unsigned long queueLength (TYPE_3__*) ; 
 scalar_t__ registerJob (TYPE_4__*) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sdsdup (char*) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_10__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setJobAssociatedValue (TYPE_4__*,TYPE_5__*) ; 
 TYPE_7__ shared ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  updateJobAwakeTime (TYPE_4__*,int /*<<< orphan*/ ) ; 

void addjobCommand(client *c) {
    long long replicate = server.cluster->size > 3 ? 3 : server.cluster->size;
    long long ttl = 3600*24;
    long long retry = -1;
    long long delay = 0;
    long long maxlen = 0; /* Max queue length for job to be accepted. */
    mstime_t timeout;
    int j, retval;
    int async = 0;  /* Asynchronous request? */
    int extrepl = getMemoryWarningLevel() > 0; /* Replicate externally? */
    int leaving = myselfLeaving();
    static uint64_t prev_ctime = 0;

    /* Another case for external replication, other than memory pressure, is
     * if this node is leaving the cluster. In this case we don't want to create
     * new messages here. */
    if (leaving) extrepl = 1;

    /* Parse args. */
    for (j = 4; j < c->argc; j++) {
        char *opt = c->argv[j]->ptr;
        int lastarg = j == c->argc-1;
        if (!strcasecmp(opt,"replicate") && !lastarg) {
            retval = getLongLongFromObject(c->argv[j+1],&replicate);
            if (retval != C_OK || replicate <= 0 || replicate > 65535) {
                addReplyError(c,"REPLICATE must be between 1 and 65535");
                return;
            }
            j++;
        } else if (!strcasecmp(opt,"ttl") && !lastarg) {
            retval = getLongLongFromObject(c->argv[j+1],&ttl);
            if (retval != C_OK || ttl <= 0) {
                addReplyError(c,"TTL must be a number > 0");
                return;
            }
            j++;
        } else if (!strcasecmp(opt,"retry") && !lastarg) {
            retval = getLongLongFromObject(c->argv[j+1],&retry);
            if (retval != C_OK || retry < 0) {
                addReplyError(c,"RETRY time must be a non negative number");
                return;
            }
            j++;
        } else if (!strcasecmp(opt,"delay") && !lastarg) {
            retval = getLongLongFromObject(c->argv[j+1],&delay);
            if (retval != C_OK || delay < 0) {
                addReplyError(c,"DELAY time must be a non negative number");
                return;
            }
            j++;
        } else if (!strcasecmp(opt,"maxlen") && !lastarg) {
            retval = getLongLongFromObject(c->argv[j+1],&maxlen);
            if (retval != C_OK || maxlen <= 0) {
                addReplyError(c,"MAXLEN must be a positive number");
                return;
            }
            j++;
        } else if (!strcasecmp(opt,"async")) {
            async = 1;
        } else {
            addReply(c,shared.syntaxerr);
            return;
        }
    }

    /* Parse the timeout argument. */
    if (getTimeoutFromObjectOrReply(c,c->argv[3],&timeout,UNIT_MILLISECONDS)
        != C_OK) return;

    /* REPLICATE > 1 and RETRY set to 0 does not make sense, why to replicate
     * the job if it will never try to be re-queued if case the job processing
     * is not acknowledged? */
    if (replicate > 1 && retry == 0) {
        addReplyError(c,"With RETRY set to 0 please explicitly set  "
                        "REPLICATE to 1 (at-most-once delivery)");
        return;
    }

    /* DELAY greater or equal to TTL is silly. */
    if (delay >= ttl) {
        addReplyError(c,"The specified DELAY is greater than TTL. Job refused "
                        "since would never be delivered");
        return;
    }

    /* When retry is not specified, it defaults to 1/10 of the TTL, with
     * an hard limit of JOB_DEFAULT_RETRY_MAX seconds (5 minutes normally). */
    if (retry == -1) {
        retry = ttl/10;
        if (retry > JOB_DEFAULT_RETRY_MAX) retry = JOB_DEFAULT_RETRY_MAX;
        if (retry == 0) retry = 1;
    }

    /* Check if REPLICATE can't be honoured at all. */
    int additional_nodes = extrepl ? replicate : replicate-1;

    if (additional_nodes > server.cluster->reachable_nodes_count) {
        if (extrepl &&
            additional_nodes-1 == server.cluster->reachable_nodes_count)
        {
            addReplySds(c,
                sdscatprintf(sdsempty(),
                       "-NOREPL Not enough reachable nodes "
                       "for the requested replication level, since I'm unable "
                       "to hold a copy of the message for the following "
                       "reason: %s\r\n",
                       leaving ? "I'm leaving the cluster" :
                                 "I'm out of memory"));
        } else {
            addReplySds(c,
                sdsnew("-NOREPL Not enough reachable nodes "
                       "for the requested replication level\r\n"));
        }
        return;
    }

    /* Lookup the queue by the name, in order to perform checks for
     * MAXLEN and to check for paused queue. */
    queue *q = lookupQueue(c->argv[1]);

    /* If maxlen was specified, check that the local queue len is
     * within the requested limits. */
    if (maxlen && q && queueLength(q) >= (unsigned long) maxlen) {
        addReplySds(c,
            sdsnew("-MAXLEN Queue is already longer than "
                   "the specified MAXLEN count\r\n"));
        return;
    }

    /* If the queue is paused in input, refuse the job. */
    if (q && q->flags & QUEUE_FLAG_PAUSED_IN) {
        addReplySds(c,
            sdsnew("-PAUSED Queue paused in input, try later\r\n"));
        return;
    }

    /* Are we going to discard the local copy before to return to the caller?
     * This happens when the job is at the same type asynchronously
     * replicated AND because of memory warning level we are going to
     * replicate externally without taking a copy. */
    int discard_local_copy = async && extrepl;

    /* Create a new job. */
    job *job = createJob(NULL,JOB_STATE_WAIT_REPL,ttl,retry);
    job->queue = c->argv[1];
    incrRefCount(c->argv[1]);
    job->repl = replicate;

    /* If no external replication is used, add myself to the list of nodes
     * that have a copy of the job. */
    if (!extrepl)
        dictAdd(job->nodes_delivered,myself->name,myself);

    /* Job ctime is milliseconds * 1000000. Jobs created in the same
     * millisecond gets an incremental ctime. The ctime is used to sort
     * queues, so we have some weak sorting semantics for jobs: non-requeued
     * jobs are delivered roughly in the order they are added into a given
     * node. */
    job->ctime = mstime()*1000000;
    if (job->ctime <= prev_ctime) job->ctime = prev_ctime+1;
    prev_ctime = job->ctime;

    job->etime = server.unixtime + ttl;
    job->delay = delay;
    job->retry = retry;
    job->body = sdsdup(c->argv[2]->ptr);

    /* Set the next time the job will be queued. Note that once we call
     * enqueueJob() the first time, this will be set to 0 (never queue
     * again) for jobs that have a zero retry value (at most once jobs). */
    if (delay) {
        job->qtime = server.mstime + delay*1000;
    } else {
        /* This will be updated anyway by enqueueJob(). */
        job->qtime = server.mstime + retry*1000;
    }

    /* Register the job locally, unless we are going to remove it locally. */
    if (!discard_local_copy && registerJob(job) == C_ERR) {
        /* A job ID with the same name? Practically impossible but
         * let's handle it to trap possible bugs in a cleaner way. */
        serverLog(LL_WARNING,"ID already existing in ADDJOB command!");
        freeJob(job);
        addReplyError(c,"Internal error creating the job, check server logs");
        return;
    }

    /* For replicated messages where ASYNC option was not asked, block
     * the client, and wait for acks. Otherwise if no synchronous replication
     * is used or if we don't have additional copies to deliver, we just queue
     * the job and return to the client ASAP.
     *
     * Note that for REPLICATE > 1 and ASYNC the replication process is
     * best effort. */
    if ((replicate > 1 || extrepl) && !async) {
        c->bpop.timeout = timeout;
        c->bpop.job = job;
        c->bpop.added_node_time = mstime();
        blockClient(c,BLOCKED_JOB_REPL);
        setJobAssociatedValue(job,c);
        /* Create the nodes_confirmed dictionary only if we actually need
         * it for synchronous replication. It will be released later
         * when we move away from JOB_STATE_WAIT_REPL. */
        job->nodes_confirmed = dictCreate(&clusterNodesDictType,NULL);
        /* Confirm itself as an acknowledged receiver if this node will
         * retain a copy of the job. */
        if (!extrepl) dictAdd(job->nodes_confirmed,myself->name,myself);
    } else {
        if (job->delay == 0) {
            if (!extrepl) enqueueJob(job,0); /* Will change the job state. */
        } else {
            /* Delayed jobs that don't wait for replication can move
             * forward to ACTIVE state ASAP, and get scheduled for
             * queueing. */
            job->state = JOB_STATE_ACTIVE;
            if (!discard_local_copy) updateJobAwakeTime(job,0);
        }
        addReplyJobID(c,job);
        if (!extrepl) AOFLoadJob(job);
    }

    /* If the replication factor is > 1, send REPLJOB messages to REPLICATE-1
     * nodes. */
    if (additional_nodes > 0)
        clusterReplicateJob(job, additional_nodes, async);

    /* If the job is asynchronously and externally replicated at the same time,
     * send an ENQUEUE message ASAP to one random node, and delete the job from
     * this node right now. */
    if (discard_local_copy) {
        dictEntry *de = dictGetRandomKey(job->nodes_delivered);
        if (de) {
            clusterNode *n = dictGetVal(de);
            clusterSendEnqueue(n,job,job->delay);
        }
        /* We don't have to unregister the job since we did not registered
         * it if it's async + extrepl. */
        freeJob(job);
    }
}