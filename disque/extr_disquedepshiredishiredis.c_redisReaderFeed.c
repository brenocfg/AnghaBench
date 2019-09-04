#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * sds ;
struct TYPE_4__ {scalar_t__ len; scalar_t__ maxbuf; int /*<<< orphan*/ * buf; scalar_t__ pos; scalar_t__ err; } ;
typedef  TYPE_1__ redisReader ;

/* Variables and functions */
 int REDIS_ERR ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  __redisReaderSetErrorOOM (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ sdsavail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdscatlen (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/ * sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 scalar_t__ sdslen (int /*<<< orphan*/ *) ; 

int redisReaderFeed(redisReader *r, const char *buf, size_t len) {
    sds newbuf;

    /* Return early when this reader is in an erroneous state. */
    if (r->err)
        return REDIS_ERR;

    /* Copy the provided buffer. */
    if (buf != NULL && len >= 1) {
        /* Destroy internal buffer when it is empty and is quite large. */
        if (r->len == 0 && r->maxbuf != 0 && sdsavail(r->buf) > r->maxbuf) {
            sdsfree(r->buf);
            r->buf = sdsempty();
            r->pos = 0;

            /* r->buf should not be NULL since we just free'd a larger one. */
            assert(r->buf != NULL);
        }

        newbuf = sdscatlen(r->buf,buf,len);
        if (newbuf == NULL) {
            __redisReaderSetErrorOOM(r);
            return REDIS_ERR;
        }

        r->buf = newbuf;
        r->len = sdslen(r->buf);
    }

    return REDIS_OK;
}