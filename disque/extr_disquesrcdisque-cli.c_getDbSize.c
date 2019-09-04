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
struct TYPE_4__ {scalar_t__ type; int integer; } ;
typedef  TYPE_1__ redisReply ;

/* Variables and functions */
 scalar_t__ REDIS_REPLY_INTEGER ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 TYPE_1__* redisCommand (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int getDbSize(void) {
    redisReply *reply;
    int size;

    reply = redisCommand(context, "DBSIZE");

    if(reply == NULL || reply->type != REDIS_REPLY_INTEGER) {
        fprintf(stderr, "Couldn't determine DBSIZE!\n");
        exit(1);
    }

    /* Grab the number of keys and free our reply */
    size = reply->integer;
    freeReplyObject(reply);

    return size;
}