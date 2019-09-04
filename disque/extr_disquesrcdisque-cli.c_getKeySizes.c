#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int elements; scalar_t__ type; unsigned long long integer; TYPE_1__** element; } ;
typedef  TYPE_2__ redisReply ;
struct TYPE_10__ {int err; char* errstr; } ;
struct TYPE_8__ {char* str; } ;

/* Variables and functions */
 scalar_t__ REDIS_OK ; 
 scalar_t__ REDIS_REPLY_INTEGER ; 
 int TYPE_NONE ; 
 TYPE_3__* context ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_2__*) ; 
 int /*<<< orphan*/  redisAppendCommand (TYPE_3__*,char*,char*,char*) ; 
 scalar_t__ redisGetReply (TYPE_3__*,void**) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void getKeySizes(redisReply *keys, int *types,
                        unsigned long long *sizes)
{
    redisReply *reply;
    char *sizecmds[] = {"STRLEN","LLEN","SCARD","HLEN","ZCARD"};
    unsigned int i;

    /* Pipeline size commands */
    for(i=0;i<keys->elements;i++) {
        /* Skip keys that were deleted */
        if(types[i]==TYPE_NONE)
            continue;

        redisAppendCommand(context, "%s %s", sizecmds[types[i]],
            keys->element[i]->str);
    }

    /* Retrieve sizes */
    for(i=0;i<keys->elements;i++) {
        /* Skip keys that disappeared between SCAN and TYPE */
        if(types[i] == TYPE_NONE) {
            sizes[i] = 0;
            continue;
        }

        /* Retrieve size */
        if(redisGetReply(context, (void**)&reply)!=REDIS_OK) {
            fprintf(stderr, "Error getting size for key '%s' (%d: %s)\n",
                keys->element[i]->str, context->err, context->errstr);
            exit(1);
        } else if(reply->type != REDIS_REPLY_INTEGER) {
            /* Theoretically the key could have been removed and
             * added as a different type between TYPE and SIZE */
            fprintf(stderr,
                "Warning:  %s on '%s' failed (may have changed type)\n",
                 sizecmds[types[i]], keys->element[i]->str);
            sizes[i] = 0;
        } else {
            sizes[i] = reply->integer;
        }

        freeReplyObject(reply);
    }
}