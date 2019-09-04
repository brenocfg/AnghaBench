#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ btype; int flags; } ;
typedef  TYPE_1__ client ;
struct TYPE_8__ {int /*<<< orphan*/  unblocked_clients; int /*<<< orphan*/  bpop_blocked_clients; } ;

/* Variables and functions */
 scalar_t__ BLOCKED_GETJOB ; 
 scalar_t__ BLOCKED_JOB_REPL ; 
 scalar_t__ BLOCKED_NONE ; 
 int CLIENT_BLOCKED ; 
 int CLIENT_UNBLOCKED ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/  unblockClientBlockedForJobs (TYPE_1__*) ; 
 int /*<<< orphan*/  unblockClientWaitingJobRepl (TYPE_1__*) ; 

void unblockClient(client *c) {
    if (c->btype == BLOCKED_JOB_REPL) {
        unblockClientWaitingJobRepl(c);
    } else if (c->btype == BLOCKED_GETJOB) {
        unblockClientBlockedForJobs(c);
    } else {
        serverPanic("Unknown btype in unblockClient().");
    }
    /* Clear the flags, and put the client in the unblocked list so that
     * we'll process new commands in its query buffer ASAP. */
    c->flags &= ~CLIENT_BLOCKED;
    c->btype = BLOCKED_NONE;
    server.bpop_blocked_clients--;
    /* The client may already be into the unblocked list because of a previous
     * blocking operation, don't add back it into the list multiple times. */
    if (!(c->flags & CLIENT_UNBLOCKED)) {
        c->flags |= CLIENT_UNBLOCKED;
        listAddNodeTail(server.unblocked_clients,c);
    }
}