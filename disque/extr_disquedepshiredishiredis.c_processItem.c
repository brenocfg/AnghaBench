#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t ridx; TYPE_2__* rstack; } ;
typedef  TYPE_1__ redisReader ;
struct TYPE_10__ {int type; } ;
typedef  TYPE_2__ redisReadTask ;

/* Variables and functions */
 int REDIS_ERR ; 
#define  REDIS_REPLY_ARRAY 132 
#define  REDIS_REPLY_ERROR 131 
#define  REDIS_REPLY_INTEGER 130 
#define  REDIS_REPLY_STATUS 129 
#define  REDIS_REPLY_STRING 128 
 int /*<<< orphan*/  __redisReaderSetErrorProtocolByte (TYPE_1__*,char) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int processBulkItem (TYPE_1__*) ; 
 int processLineItem (TYPE_1__*) ; 
 int processMultiBulkItem (TYPE_1__*) ; 
 char* readBytes (TYPE_1__*,int) ; 

__attribute__((used)) static int processItem(redisReader *r) {
    redisReadTask *cur = &(r->rstack[r->ridx]);
    char *p;

    /* check if we need to read type */
    if (cur->type < 0) {
        if ((p = readBytes(r,1)) != NULL) {
            switch (p[0]) {
            case '-':
                cur->type = REDIS_REPLY_ERROR;
                break;
            case '+':
                cur->type = REDIS_REPLY_STATUS;
                break;
            case ':':
                cur->type = REDIS_REPLY_INTEGER;
                break;
            case '$':
                cur->type = REDIS_REPLY_STRING;
                break;
            case '*':
                cur->type = REDIS_REPLY_ARRAY;
                break;
            default:
                __redisReaderSetErrorProtocolByte(r,*p);
                return REDIS_ERR;
            }
        } else {
            /* could not consume 1 byte */
            return REDIS_ERR;
        }
    }

    /* process typed item */
    switch(cur->type) {
    case REDIS_REPLY_ERROR:
    case REDIS_REPLY_STATUS:
    case REDIS_REPLY_INTEGER:
        return processLineItem(r);
    case REDIS_REPLY_STRING:
        return processBulkItem(r);
    case REDIS_REPLY_ARRAY:
        return processMultiBulkItem(r);
    default:
        assert(NULL);
        return REDIS_ERR; /* Avoid warning. */
    }
}