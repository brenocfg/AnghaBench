#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_10__ {int /*<<< orphan*/ * clients; } ;
typedef  TYPE_2__ queue ;
typedef  int /*<<< orphan*/  mstime_t ;
struct TYPE_9__ {int /*<<< orphan*/  queues; int /*<<< orphan*/  flags; int /*<<< orphan*/  timeout; } ;
struct TYPE_11__ {TYPE_1__ bpop; } ;
typedef  TYPE_3__ client ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKED_GETJOB ; 
 scalar_t__ DICT_OK ; 
 int /*<<< orphan*/  blockClient (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* createQueue (int /*<<< orphan*/ *) ; 
 scalar_t__ dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * listCreate () ; 
 TYPE_2__* lookupQueue (int /*<<< orphan*/ *) ; 

void blockForJobs(client *c, robj **queues, int numqueues, mstime_t timeout, uint64_t flags) {
    int j;

    c->bpop.timeout = timeout;
    c->bpop.flags = flags;
    for (j = 0; j < numqueues; j++) {
        queue *q = lookupQueue(queues[j]);
        if (!q) q = createQueue(queues[j]);

        /* Handle duplicated queues in array. */
        if (dictAdd(c->bpop.queues,queues[j],NULL) != DICT_OK) continue;
        incrRefCount(queues[j]);

        /* Add this client to the list of clients in the queue. */
        if (q->clients == NULL) q->clients = listCreate();
        listAddNodeTail(q->clients,c);
    }
    blockClient(c,BLOCKED_GETJOB);
}