#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct client {int fd; int /*<<< orphan*/  reply; int /*<<< orphan*/ * peerid; scalar_t__ obuf_soft_limit_reached_time; scalar_t__ reply_bytes; int /*<<< orphan*/  btype; int /*<<< orphan*/  flags; scalar_t__ bufpos; int /*<<< orphan*/ * argv; scalar_t__ argc; scalar_t__ querybuf_peak; int /*<<< orphan*/  querybuf; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKED_NONE ; 
 int /*<<< orphan*/  CLIENT_AOF_CLIENT ; 
 int /*<<< orphan*/  decrRefCountVoid ; 
 int /*<<< orphan*/  dupClientReplyValue ; 
 int /*<<< orphan*/  listCreate () ; 
 int /*<<< orphan*/  listSetDupMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listSetFreeMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 struct client* zmalloc (int) ; 

struct client *createFakeClient(void) {
    struct client *c = zmalloc(sizeof(*c));

    c->fd = -1;
    c->name = NULL;
    c->querybuf = sdsempty();
    c->querybuf_peak = 0;
    c->argc = 0;
    c->argv = NULL;
    c->bufpos = 0;
    c->flags = CLIENT_AOF_CLIENT;
    c->btype = BLOCKED_NONE;
    c->reply = listCreate();
    c->reply_bytes = 0;
    c->obuf_soft_limit_reached_time = 0;
    c->peerid = NULL;
    listSetFreeMethod(c->reply,decrRefCountVoid);
    listSetDupMethod(c->reply,dupClientReplyValue);
    return c;
}