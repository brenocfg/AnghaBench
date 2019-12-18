#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; scalar_t__ fd; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {int /*<<< orphan*/  clients_pending_write; } ;

/* Variables and functions */
 int CLIENT_AOF_CLIENT ; 
 int CLIENT_PENDING_WRITE ; 
 int CLIENT_REPLY_OFF ; 
 int CLIENT_REPLY_SKIP ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  clientHasPendingReplies (TYPE_1__*) ; 
 int /*<<< orphan*/  listAddNodeHead (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__ server ; 

int prepareClientToWrite(client *c) {
    /* CLIENT REPLY OFF / SKIP handling: don't send replies. */
    if (c->flags & (CLIENT_REPLY_OFF|CLIENT_REPLY_SKIP)) return C_ERR;
    if (c->flags & CLIENT_AOF_CLIENT) return C_ERR;
    if (c->fd <= 0) return C_ERR; /* Fake client */

    /* Schedule the client to write the output buffers to the socket only
     * if not already done (there were no pending writes already and the client
     * was yet not flagged), and, for slaves, if the slave can actually
     * receive writes at this stage. */
    if (!clientHasPendingReplies(c) &&
        !(c->flags & CLIENT_PENDING_WRITE))
    {
        /* Here instead of installing the write handler, we just flag the
         * client and put it into a list of clients that have something
         * to write to the socket. This way before re-entering the event
         * loop, we can try to directly write to the client sockets avoiding
         * a system call. We'll only really install the write handler if
         * we'll not be able to write the whole reply at once. */
        c->flags |= CLIENT_PENDING_WRITE;
        listAddNodeHead(server.clients_pending_write,c);
    }

    /* Authorize the caller to queue in the output buffer of this client. */
    return C_OK;
}