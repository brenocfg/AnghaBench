#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_5__ {scalar_t__ clients; scalar_t__ needjobs_responders; int /*<<< orphan*/  sl; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ queue ;
struct TYPE_6__ {int /*<<< orphan*/  queues; } ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictRelease (scalar_t__) ; 
 scalar_t__ listLength (scalar_t__) ; 
 int /*<<< orphan*/  listRelease (scalar_t__) ; 
 TYPE_1__* lookupQueue (int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  skiplistFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

int destroyQueue(robj *name) {
    queue *q = lookupQueue(name);
    if (!q) return C_ERR;

    dictDelete(server.queues,name);
    decrRefCount(q->name);
    skiplistFree(q->sl);
    if (q->needjobs_responders) dictRelease(q->needjobs_responders);
    if (q->clients) {
        serverAssert(listLength(q->clients) == 0);
        listRelease(q->clients);
    }
    zfree(q);
    return C_OK;
}