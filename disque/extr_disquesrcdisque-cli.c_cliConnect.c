#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* hostsocket; char* hostip; int hostport; } ;
struct TYPE_6__ {char* errstr; int /*<<< orphan*/  fd; scalar_t__ err; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISQUE_CLI_KEEPALIVE_INTERVAL ; 
 int REDIS_ERR ; 
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  anetKeepAlive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cliAuth () ; 
 scalar_t__ cliSelect () ; 
 TYPE_5__ config ; 
 TYPE_1__* context ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* redisConnect (char*,int) ; 
 TYPE_1__* redisConnectUnix (char*) ; 
 int /*<<< orphan*/  redisFree (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int cliConnect(int force) {
    if (context == NULL || force) {
        if (context != NULL)
            redisFree(context);

        if (config.hostsocket == NULL) {
            context = redisConnect(config.hostip,config.hostport);
        } else {
            context = redisConnectUnix(config.hostsocket);
        }

        if (context->err) {
            fprintf(stderr,"Could not connect to Disque at ");
            if (config.hostsocket == NULL)
                fprintf(stderr,"%s:%d: %s\n",config.hostip,config.hostport,context->errstr);
            else
                fprintf(stderr,"%s: %s\n",config.hostsocket,context->errstr);
            redisFree(context);
            context = NULL;
            return REDIS_ERR;
        }

        /* Set aggressive KEEP_ALIVE socket option in the Disque context socket
         * in order to prevent timeouts caused by the execution of long
         * commands. At the same time this improves the detection of real
         * errors. */
        anetKeepAlive(NULL, context->fd, DISQUE_CLI_KEEPALIVE_INTERVAL);

        /* Do AUTH and select the right DB. */
        if (cliAuth() != REDIS_OK)
            return REDIS_ERR;
        if (cliSelect() != REDIS_OK)
            return REDIS_ERR;
    }
    return REDIS_OK;
}