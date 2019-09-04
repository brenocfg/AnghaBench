#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisReply ;
struct TYPE_2__ {int /*<<< orphan*/ * auth; } ;

/* Variables and functions */
 int REDIS_ERR ; 
 int REDIS_OK ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  freeReplyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * redisCommand (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cliAuth() {
    redisReply *reply;
    if (config.auth == NULL) return REDIS_OK;

    reply = redisCommand(context,"AUTH %s",config.auth);
    if (reply != NULL) {
        freeReplyObject(reply);
        return REDIS_OK;
    }
    return REDIS_ERR;
}