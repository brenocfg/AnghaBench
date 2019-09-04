#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int mstime_t ;
struct TYPE_10__ {int timeout; } ;
struct TYPE_11__ {int flags; scalar_t__ lastinteraction; TYPE_1__ bpop; } ;
typedef  TYPE_2__ client ;
struct TYPE_13__ {scalar_t__ maxidletime; } ;
struct TYPE_12__ {int /*<<< orphan*/  leavingerr; } ;

/* Variables and functions */
 int CLIENT_BLOCKED ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeClient (TYPE_2__*) ; 
 scalar_t__ myselfLeaving () ; 
 int /*<<< orphan*/  replyToBlockedClientTimedOut (TYPE_2__*) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__ shared ; 
 int /*<<< orphan*/  unblockClient (TYPE_2__*) ; 

int clientsCronHandleTimeout(client *c, mstime_t now_ms) {
    time_t now = now_ms/1000;

    if (server.maxidletime &&
        !(c->flags & CLIENT_BLOCKED) &&  /* no timeout for blocked clients. */
        (now - c->lastinteraction > server.maxidletime))
    {
        serverLog(LL_VERBOSE,"Closing idle client");
        freeClient(c);
        return 1;
    } else if (c->flags & CLIENT_BLOCKED) {
        /* Blocked OPS timeout is handled with milliseconds resolution.
         * However note that the actual resolution is limited by
         * server.hz. */

        if (c->bpop.timeout != 0 && c->bpop.timeout < now_ms) {
            replyToBlockedClientTimedOut(c);
            unblockClient(c);
        } else if (myselfLeaving()) {
            addReply(c,shared.leavingerr);
            unblockClient(c);
        }
    }
    return 0;
}