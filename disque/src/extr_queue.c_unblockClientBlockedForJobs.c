#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_9__ {int /*<<< orphan*/ * clients; } ;
typedef  TYPE_2__ queue ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_8__ {int /*<<< orphan*/  queues; } ;
struct TYPE_10__ {TYPE_1__ bpop; } ;
typedef  TYPE_3__ client ;

/* Variables and functions */
 int /*<<< orphan*/  GCQueue (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_MAX_IDLE_TIME ; 
 int /*<<< orphan*/  dictEmpty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ listLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listSearchKey (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_2__* lookupQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 

void unblockClientBlockedForJobs(client *c) {
    dictEntry *de;
    dictIterator *di;

    di = dictGetIterator(c->bpop.queues);
    while((de = dictNext(di)) != NULL) {
        robj *qname = dictGetKey(de);
        queue *q = lookupQueue(qname);
        serverAssert(q != NULL);

        listDelNode(q->clients,listSearchKey(q->clients,c));
        if (listLength(q->clients) == 0) {
            listRelease(q->clients);
            q->clients = NULL;
            GCQueue(q,QUEUE_MAX_IDLE_TIME);
        }
    }
    dictReleaseIterator(di);
    dictEmpty(c->bpop.queues,NULL);
}