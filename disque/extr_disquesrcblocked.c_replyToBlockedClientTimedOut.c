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
struct TYPE_6__ {scalar_t__ btype; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {int /*<<< orphan*/  nullmultibulk; } ;

/* Variables and functions */
 scalar_t__ BLOCKED_GETJOB ; 
 scalar_t__ BLOCKED_JOB_REPL ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplySds (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 TYPE_2__ shared ; 

void replyToBlockedClientTimedOut(client *c) {
    if (c->btype == BLOCKED_JOB_REPL) {
        addReplySds(c,
            sdsnew("-NOREPL Timeout reached before replicating to "
                   "the requested number of nodes\r\n"));
        return;
    } else if (c->btype == BLOCKED_GETJOB) {
        addReply(c,shared.nullmultibulk);
    } else {
        serverPanic("Unknown btype in replyToBlockedClientTimedOut().");
    }
}