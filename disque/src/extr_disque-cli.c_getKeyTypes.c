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
struct TYPE_9__ {unsigned int elements; scalar_t__ type; int /*<<< orphan*/  str; TYPE_1__** element; } ;
typedef  TYPE_2__ redisReply ;
struct TYPE_10__ {int err; char* errstr; } ;
struct TYPE_8__ {char* str; } ;

/* Variables and functions */
 scalar_t__ REDIS_OK ; 
 scalar_t__ REDIS_REPLY_STATUS ; 
 TYPE_3__* context ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_2__*) ; 
 int /*<<< orphan*/  redisAppendCommand (TYPE_3__*,char*,char*) ; 
 scalar_t__ redisGetReply (TYPE_3__*,void**) ; 
 int /*<<< orphan*/  stderr ; 
 int toIntType (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void getKeyTypes(redisReply *keys, int *types) {
    redisReply *reply;
    unsigned int i;

    /* Pipeline TYPE commands */
    for(i=0;i<keys->elements;i++) {
        redisAppendCommand(context, "TYPE %s", keys->element[i]->str);
    }

    /* Retrieve types */
    for(i=0;i<keys->elements;i++) {
        if(redisGetReply(context, (void**)&reply)!=REDIS_OK) {
            fprintf(stderr, "Error getting type for key '%s' (%d: %s)\n",
                keys->element[i]->str, context->err, context->errstr);
            exit(1);
        } else if(reply->type != REDIS_REPLY_STATUS) {
            fprintf(stderr, "Invalid reply type (%d) for TYPE on key '%s'!\n",
                reply->type, keys->element[i]->str);
            exit(1);
        }

        types[i] = toIntType(keys->element[i]->str, reply->str);
        freeReplyObject(reply);
    }
}