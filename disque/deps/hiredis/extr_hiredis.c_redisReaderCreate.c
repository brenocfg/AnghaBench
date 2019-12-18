#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* errstr; int ridx; int /*<<< orphan*/ * buf; int /*<<< orphan*/  maxbuf; int /*<<< orphan*/ * fn; scalar_t__ err; } ;
typedef  TYPE_1__ redisReader ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_READER_MAX_BUF ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  defaultFunctions ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * sdsempty () ; 

redisReader *redisReaderCreate(void) {
    redisReader *r;

    r = calloc(sizeof(redisReader),1);
    if (r == NULL)
        return NULL;

    r->err = 0;
    r->errstr[0] = '\0';
    r->fn = &defaultFunctions;
    r->buf = sdsempty();
    r->maxbuf = REDIS_READER_MAX_BUF;
    if (r->buf == NULL) {
        free(r);
        return NULL;
    }

    r->ridx = -1;
    return r;
}