#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_13__ {int flags; } ;
typedef  TYPE_1__ queue ;
struct TYPE_14__ {int argc; TYPE_7__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_16__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_15__ {int /*<<< orphan*/  syntaxerr; } ;

/* Variables and functions */
 int QUEUE_FLAG_PAUSED_ALL ; 
 int QUEUE_FLAG_PAUSED_IN ; 
 int QUEUE_FLAG_PAUSED_OUT ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplySds (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterBroadcastPause (TYPE_7__*,int) ; 
 TYPE_1__* createQueue (TYPE_7__*) ; 
 TYPE_1__* lookupQueue (TYPE_7__*) ; 
 int /*<<< orphan*/  queueChangePausedState (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  queueGetPausedStateString (int) ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsnewlen (char*,int) ; 
 TYPE_3__ shared ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

void pauseCommand(client *c) {
    int j, bcast = 0, update = 0;
    uint32_t old_flags = 0, new_flags = 0;

    queue *q = lookupQueue(c->argv[1]);
    if (q) old_flags = q->flags;

    for (j = 2; j < c->argc; j++) {
        if (!strcasecmp(c->argv[j]->ptr,"none")) {
            new_flags = 0;
            update = 1;
        } else if (!strcasecmp(c->argv[j]->ptr,"in")) {
            new_flags |= QUEUE_FLAG_PAUSED_IN; update = 1;
        } else if (!strcasecmp(c->argv[j]->ptr,"out")) {
            new_flags |= QUEUE_FLAG_PAUSED_OUT; update = 1;
        } else if (!strcasecmp(c->argv[j]->ptr,"all")) {
            new_flags |= QUEUE_FLAG_PAUSED_ALL; update = 1;
        } else if (!strcasecmp(c->argv[j]->ptr,"state")) {
            /* Nothing to do, we reply with the state regardless. */
        } else if (!strcasecmp(c->argv[j]->ptr,"bcast")) {
            bcast = 1;
        } else {
            addReply(c,shared.syntaxerr);
            return;
        }
    }

    /* Update the queue pause state, if needed. */
    if (!q && update && old_flags != new_flags) q = createQueue(c->argv[1]);
    if (q && update) {
        queueChangePausedState(q,QUEUE_FLAG_PAUSED_IN,
            (new_flags & QUEUE_FLAG_PAUSED_IN) != 0);
        queueChangePausedState(q,QUEUE_FLAG_PAUSED_OUT,
            (new_flags & QUEUE_FLAG_PAUSED_OUT) != 0);
    }

    /* Get the queue flags after the operation. */
    new_flags = q ? q->flags : 0;
    new_flags &= QUEUE_FLAG_PAUSED_ALL;

    /* Broadcast a PAUSE command if the user specified BCAST. */
    if (bcast) clusterBroadcastPause(c->argv[1],new_flags);

    /* Always reply with the current queue state. */
    sds reply = sdsnewlen("+",1);
    reply = sdscat(reply,queueGetPausedStateString(new_flags));
    reply = sdscatlen(reply,"\r\n",2);
    addReplySds(c,reply);
}