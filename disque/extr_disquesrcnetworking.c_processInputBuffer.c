#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* querybuf; int flags; scalar_t__ reqtype; scalar_t__ argc; } ;
typedef  TYPE_1__ client ;
struct TYPE_9__ {TYPE_1__* current_client; } ;

/* Variables and functions */
 int CLIENT_BLOCKED ; 
 int CLIENT_CLOSE_AFTER_REPLY ; 
 scalar_t__ C_OK ; 
 scalar_t__ PROTO_REQ_INLINE ; 
 scalar_t__ PROTO_REQ_MULTIBULK ; 
 scalar_t__ clientsArePaused () ; 
 scalar_t__ processCommand (TYPE_1__*) ; 
 scalar_t__ processInlineBuffer (TYPE_1__*) ; 
 scalar_t__ processMultibulkBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  resetClient (TYPE_1__*) ; 
 scalar_t__ sdslen (char*) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

void processInputBuffer(client *c) {
    server.current_client = c;
    /* Keep processing while there is something in the input buffer */
    while(sdslen(c->querybuf)) {
        /* Return if clients are paused. */
        if (clientsArePaused()) break;

        /* Immediately abort if the client is in the middle of something. */
        if (c->flags & CLIENT_BLOCKED) break;

        /* CLIENT_CLOSE_AFTER_REPLY closes the connection once the reply is
         * written to the client. Make sure to not let the reply grow after
         * this flag has been set (i.e. don't process more commands). */
        if (c->flags & CLIENT_CLOSE_AFTER_REPLY) break;

        /* Determine request type when unknown. */
        if (!c->reqtype) {
            if (c->querybuf[0] == '*') {
                c->reqtype = PROTO_REQ_MULTIBULK;
            } else {
                c->reqtype = PROTO_REQ_INLINE;
            }
        }

        if (c->reqtype == PROTO_REQ_INLINE) {
            if (processInlineBuffer(c) != C_OK) break;
        } else if (c->reqtype == PROTO_REQ_MULTIBULK) {
            if (processMultibulkBuffer(c) != C_OK) break;
        } else {
            serverPanic("Unknown request type");
        }

        /* Multibulk processing could see a <= 0 length. */
        if (c->argc == 0) {
            resetClient(c);
        } else {
            /* Only reset the client when the command was executed. */
            if (processCommand(c) == C_OK)
                resetClient(c);
        }
    }
    server.current_client = NULL;
}