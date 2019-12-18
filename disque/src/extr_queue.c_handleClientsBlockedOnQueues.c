#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  clients; } ;
typedef  TYPE_2__ queue ;
struct TYPE_15__ {TYPE_4__* value; } ;
typedef  TYPE_3__ listNode ;
typedef  int /*<<< orphan*/  job ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_13__ {int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {TYPE_1__ bpop; } ;
typedef  TYPE_4__ client ;
struct TYPE_17__ {int /*<<< orphan*/  ready_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEEDJOBS_REACHED_ZERO ; 
 int /*<<< orphan*/  addReplyJob (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyMultiBulkLen (TYPE_4__*,int) ; 
 int /*<<< orphan*/  dictEmpty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 TYPE_3__* listFirst (int /*<<< orphan*/ ) ; 
 int listLength (int /*<<< orphan*/ ) ; 
 TYPE_2__* lookupQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  needJobsForQueue (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * queueFetchJob (TYPE_2__*,unsigned long*) ; 
 TYPE_6__ server ; 
 int /*<<< orphan*/  unblockClient (TYPE_4__*) ; 

void handleClientsBlockedOnQueues(void) {
    dictEntry *de;
    dictIterator *di;

    /* Don't waste time if there is nothing to do. */
    if (dictSize(server.ready_queues) == 0) return;

    di = dictGetIterator(server.ready_queues);
    while((de = dictNext(di)) != NULL) {
        queue *q = lookupQueue(dictGetKey(de));
        if (!q || !q->clients) continue;
        int numclients = listLength(q->clients);
        while(numclients--) {
            unsigned long qlen;
            listNode *ln = listFirst(q->clients);
            client *c = ln->value;
            job *j = queueFetchJob(q,&qlen);

            if (!j) break; /* No longer elements, try next queue. */
            if (qlen == 0) needJobsForQueue(q,NEEDJOBS_REACHED_ZERO);
            addReplyMultiBulkLen(c,1);
            addReplyJob(c,j,c->bpop.flags);
            unblockClient(c); /* This will remove it from q->clients. */
        }
    }
    dictReleaseIterator(di);
    dictEmpty(server.ready_queues,NULL);
}