#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listNode ;
struct TYPE_10__ {int /*<<< orphan*/  queues; } ;
struct TYPE_11__ {int flags; int /*<<< orphan*/ * peerid; struct TYPE_11__* argv; scalar_t__ name; int /*<<< orphan*/  reply; TYPE_1__ bpop; int /*<<< orphan*/ * querybuf; } ;
typedef  TYPE_2__ client ;
struct TYPE_12__ {int /*<<< orphan*/  clients_to_close; int /*<<< orphan*/  monitors; } ;

/* Variables and functions */
 int CLIENT_BLOCKED ; 
 int CLIENT_CLOSE_ASAP ; 
 int CLIENT_MONITOR ; 
 int /*<<< orphan*/  decrRefCount (scalar_t__) ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeClientArgv (TYPE_2__*) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listSearchKey (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 TYPE_6__ server ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unblockClient (TYPE_2__*) ; 
 int /*<<< orphan*/  unlinkClient (TYPE_2__*) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void freeClient(client *c) {
    listNode *ln;

    /* Free the query buffer */
    sdsfree(c->querybuf);
    c->querybuf = NULL;

    /* Deallocate structures used to block on blocking ops. */
    if (c->flags & CLIENT_BLOCKED) unblockClient(c);
    dictRelease(c->bpop.queues);

    /* Free data structures. */
    listRelease(c->reply);
    freeClientArgv(c);

    /* Unlink the client: this will close the socket, remove the I/O
     * handlers, and remove references of the client from different
     * places where active clients may be referenced. */
    unlinkClient(c);

    /* Monitors cleanup. */
    if (c->flags & CLIENT_MONITOR) {
        ln = listSearchKey(server.monitors,c);
        serverAssert(ln != NULL);
        listDelNode(server.monitors,ln);
    }

    /* If this client was scheduled for async freeing we need to remove it
     * from the queue. */
    if (c->flags & CLIENT_CLOSE_ASAP) {
        ln = listSearchKey(server.clients_to_close,c);
        serverAssert(ln != NULL);
        listDelNode(server.clients_to_close,ln);
    }

    /* Release other dynamically allocated client structure fields,
     * and finally release the client structure itself. */
    if (c->name) decrRefCount(c->name);
    zfree(c->argv);
    sdsfree(c->peerid);
    zfree(c);
}