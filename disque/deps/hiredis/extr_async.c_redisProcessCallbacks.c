#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ type; char* str; } ;
typedef  TYPE_3__ redisReply ;
struct TYPE_20__ {int flags; TYPE_2__* reader; int /*<<< orphan*/  errstr; int /*<<< orphan*/  err; int /*<<< orphan*/  obuf; } ;
typedef  TYPE_4__ redisContext ;
struct TYPE_21__ {int /*<<< orphan*/ * fn; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_5__ redisCallback ;
struct TYPE_22__ {int /*<<< orphan*/  replies; TYPE_4__ c; } ;
typedef  TYPE_6__ redisAsyncContext ;
struct TYPE_18__ {TYPE_1__* fn; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* freeObject ) (void*) ;} ;

/* Variables and functions */
 int REDIS_DISCONNECTING ; 
 int /*<<< orphan*/  REDIS_ERR_OTHER ; 
 int REDIS_FREEING ; 
 int REDIS_MONITORING ; 
 int REDIS_OK ; 
 scalar_t__ REDIS_REPLY_ERROR ; 
 int REDIS_SUBSCRIBED ; 
 int /*<<< orphan*/  __redisAsyncDisconnect (TYPE_6__*) ; 
 int /*<<< orphan*/  __redisAsyncFree (TYPE_6__*) ; 
 int /*<<< orphan*/  __redisGetSubscribeCallback (TYPE_6__*,void*,TYPE_5__*) ; 
 int /*<<< orphan*/  __redisPushCallback (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  __redisRunCallback (TYPE_6__*,TYPE_5__*,void*) ; 
 int __redisShiftCallback (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int redisGetReply (TYPE_4__*,void**) ; 
 scalar_t__ sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

void redisProcessCallbacks(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);
    redisCallback cb = {NULL, NULL, NULL};
    void *reply = NULL;
    int status;

    while((status = redisGetReply(c,&reply)) == REDIS_OK) {
        if (reply == NULL) {
            /* When the connection is being disconnected and there are
             * no more replies, this is the cue to really disconnect. */
            if (c->flags & REDIS_DISCONNECTING && sdslen(c->obuf) == 0) {
                __redisAsyncDisconnect(ac);
                return;
            }

            /* If monitor mode, repush callback */
            if(c->flags & REDIS_MONITORING) {
                __redisPushCallback(&ac->replies,&cb);
            }

            /* When the connection is not being disconnected, simply stop
             * trying to get replies and wait for the next loop tick. */
            break;
        }

        /* Even if the context is subscribed, pending regular callbacks will
         * get a reply before pub/sub messages arrive. */
        if (__redisShiftCallback(&ac->replies,&cb) != REDIS_OK) {
            /*
             * A spontaneous reply in a not-subscribed context can be the error
             * reply that is sent when a new connection exceeds the maximum
             * number of allowed connections on the server side.
             *
             * This is seen as an error instead of a regular reply because the
             * server closes the connection after sending it.
             *
             * To prevent the error from being overwritten by an EOF error the
             * connection is closed here. See issue #43.
             *
             * Another possibility is that the server is loading its dataset.
             * In this case we also want to close the connection, and have the
             * user wait until the server is ready to take our request.
             */
            if (((redisReply*)reply)->type == REDIS_REPLY_ERROR) {
                c->err = REDIS_ERR_OTHER;
                snprintf(c->errstr,sizeof(c->errstr),"%s",((redisReply*)reply)->str);
                __redisAsyncDisconnect(ac);
                return;
            }
            /* No more regular callbacks and no errors, the context *must* be subscribed or monitoring. */
            assert((c->flags & REDIS_SUBSCRIBED || c->flags & REDIS_MONITORING));
            if(c->flags & REDIS_SUBSCRIBED)
                __redisGetSubscribeCallback(ac,reply,&cb);
        }

        if (cb.fn != NULL) {
            __redisRunCallback(ac,&cb,reply);
            c->reader->fn->freeObject(reply);

            /* Proceed with free'ing when redisAsyncFree() was called. */
            if (c->flags & REDIS_FREEING) {
                __redisAsyncFree(ac);
                return;
            }
        } else {
            /* No callback for this reply. This can either be a NULL callback,
             * or there were no callbacks to begin with. Either way, don't
             * abort with an error, but simply ignore it because the client
             * doesn't know what the server will spit out over the wire. */
            c->reader->fn->freeObject(reply);
        }
    }

    /* Disconnect when there was an error reading the reply */
    if (status != REDIS_OK)
        __redisAsyncDisconnect(ac);
}