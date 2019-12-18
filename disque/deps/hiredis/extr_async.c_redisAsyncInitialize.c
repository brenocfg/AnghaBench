#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_5__ redisContext ;
struct TYPE_13__ {int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
struct TYPE_14__ {void* patterns; void* channels; TYPE_3__ invalid; } ;
struct TYPE_12__ {int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
struct TYPE_11__ {int /*<<< orphan*/ * cleanup; int /*<<< orphan*/ * delWrite; int /*<<< orphan*/ * addWrite; int /*<<< orphan*/ * delRead; int /*<<< orphan*/ * addRead; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {TYPE_4__ sub; TYPE_2__ replies; int /*<<< orphan*/ * onDisconnect; int /*<<< orphan*/ * onConnect; TYPE_1__ ev; int /*<<< orphan*/ * data; int /*<<< orphan*/ * errstr; scalar_t__ err; TYPE_5__ c; } ;
typedef  TYPE_6__ redisAsyncContext ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_CONNECTED ; 
 int /*<<< orphan*/  callbackDict ; 
 void* dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* realloc (TYPE_5__*,int) ; 

__attribute__((used)) static redisAsyncContext *redisAsyncInitialize(redisContext *c) {
    redisAsyncContext *ac;

    ac = realloc(c,sizeof(redisAsyncContext));
    if (ac == NULL)
        return NULL;

    c = &(ac->c);

    /* The regular connect functions will always set the flag REDIS_CONNECTED.
     * For the async API, we want to wait until the first write event is
     * received up before setting this flag, so reset it here. */
    c->flags &= ~REDIS_CONNECTED;

    ac->err = 0;
    ac->errstr = NULL;
    ac->data = NULL;

    ac->ev.data = NULL;
    ac->ev.addRead = NULL;
    ac->ev.delRead = NULL;
    ac->ev.addWrite = NULL;
    ac->ev.delWrite = NULL;
    ac->ev.cleanup = NULL;

    ac->onConnect = NULL;
    ac->onDisconnect = NULL;

    ac->replies.head = NULL;
    ac->replies.tail = NULL;
    ac->sub.invalid.head = NULL;
    ac->sub.invalid.tail = NULL;
    ac->sub.channels = dictCreate(&callbackDict,NULL);
    ac->sub.patterns = dictCreate(&callbackDict,NULL);
    return ac;
}