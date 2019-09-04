#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_8__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ client ;
struct TYPE_9__ {int /*<<< orphan*/  el; int /*<<< orphan*/  clients_pending_write; } ;

/* Variables and functions */
 scalar_t__ AE_ERR ; 
 int /*<<< orphan*/  AE_WRITABLE ; 
 int /*<<< orphan*/  CLIENT_PENDING_WRITE ; 
 scalar_t__ C_ERR ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ clientHasPendingReplies (TYPE_1__*) ; 
 int /*<<< orphan*/  freeClientAsync (TYPE_1__*) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 TYPE_1__* listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sendReplyToClient ; 
 TYPE_3__ server ; 
 scalar_t__ writeToClient (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

int handleClientsWithPendingWrites(void) {
    listIter li;
    listNode *ln;
    int processed = listLength(server.clients_pending_write);

    listRewind(server.clients_pending_write,&li);
    while((ln = listNext(&li))) {
        client *c = listNodeValue(ln);
        c->flags &= ~CLIENT_PENDING_WRITE;
        listDelNode(server.clients_pending_write,ln);

        /* Try to write buffers to the client socket. */
        if (writeToClient(c->fd,c,0) == C_ERR) continue;

        /* If there is nothing left, do nothing. Otherwise install
         * the write handler. */
        if (clientHasPendingReplies(c) &&
            aeCreateFileEvent(server.el, c->fd, AE_WRITABLE,
                sendReplyToClient, c) == AE_ERR)
        {
            freeClientAsync(c);
        }
    }
    return processed;
}