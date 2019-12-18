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
struct TYPE_7__ {size_t ridx; char* buf; int pos; int len; void* reply; TYPE_1__* fn; int /*<<< orphan*/ * rstack; } ;
typedef  TYPE_2__ redisReader ;
typedef  int /*<<< orphan*/  redisReadTask ;
struct TYPE_6__ {void* (* createString ) (int /*<<< orphan*/ *,char*,long) ;void* (* createNil ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int REDIS_ERR ; 
 int REDIS_OK ; 
 scalar_t__ REDIS_REPLY_NIL ; 
 scalar_t__ REDIS_REPLY_STRING ; 
 int /*<<< orphan*/  __redisReaderSetErrorOOM (TYPE_2__*) ; 
 int /*<<< orphan*/  moveToNextTask (TYPE_2__*) ; 
 long readLongLong (char*) ; 
 char* seekNewline (char*,int) ; 
 void* stub1 (int /*<<< orphan*/ *) ; 
 void* stub2 (int /*<<< orphan*/ *,char*,long) ; 

__attribute__((used)) static int processBulkItem(redisReader *r) {
    redisReadTask *cur = &(r->rstack[r->ridx]);
    void *obj = NULL;
    char *p, *s;
    long len;
    unsigned long bytelen;
    int success = 0;

    p = r->buf+r->pos;
    s = seekNewline(p,r->len-r->pos);
    if (s != NULL) {
        p = r->buf+r->pos;
        bytelen = s-(r->buf+r->pos)+2; /* include \r\n */
        len = readLongLong(p);

        if (len < 0) {
            /* The nil object can always be created. */
            if (r->fn && r->fn->createNil)
                obj = r->fn->createNil(cur);
            else
                obj = (void*)REDIS_REPLY_NIL;
            success = 1;
        } else {
            /* Only continue when the buffer contains the entire bulk item. */
            bytelen += len+2; /* include \r\n */
            if (r->pos+bytelen <= r->len) {
                if (r->fn && r->fn->createString)
                    obj = r->fn->createString(cur,s+2,len);
                else
                    obj = (void*)REDIS_REPLY_STRING;
                success = 1;
            }
        }

        /* Proceed when obj was created. */
        if (success) {
            if (obj == NULL) {
                __redisReaderSetErrorOOM(r);
                return REDIS_ERR;
            }

            r->pos += bytelen;

            /* Set reply if this is the root object. */
            if (r->ridx == 0) r->reply = obj;
            moveToNextTask(r);
            return REDIS_OK;
        }
    }

    return REDIS_ERR;
}