#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisReply ;
struct TYPE_7__ {int err; char* errstr; } ;
typedef  TYPE_1__ redisContext ;
struct TYPE_8__ {int /*<<< orphan*/  hostport; int /*<<< orphan*/  hostip; } ;

/* Variables and functions */
 int REDIS_ERR_EOF ; 
 int REDIS_ERR_IO ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__ config ; 
 TYPE_1__* context ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * redisCommand (TYPE_1__*,char*) ; 
 TYPE_1__* redisConnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisFree (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static redisReply *reconnectingInfo(void) {
    redisContext *c = context;
    redisReply *reply = NULL;
    int tries = 0;

    assert(!c->err);
    while(reply == NULL) {
        while (c->err & (REDIS_ERR_IO | REDIS_ERR_EOF)) {
            printf("Reconnecting (%d)...\r", ++tries);
            fflush(stdout);

            redisFree(c);
            c = redisConnect(config.hostip,config.hostport);
            usleep(1000000);
        }

        reply = redisCommand(c,"INFO");
        if (c->err && !(c->err & (REDIS_ERR_IO | REDIS_ERR_EOF))) {
            fprintf(stderr, "Error: %s\n", c->errstr);
            exit(1);
        } else if (tries > 0) {
            printf("\n");
        }
    }

    context = c;
    return reply;
}