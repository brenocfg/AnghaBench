#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int argc; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_14__ {int /*<<< orphan*/ * configfile; } ;
struct TYPE_13__ {int /*<<< orphan*/  ok; } ;
struct TYPE_11__ {scalar_t__ ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  configGetCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  configSetCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  resetCommandTableStats () ; 
 int /*<<< orphan*/  resetServerStats () ; 
 int rewriteConfig (int /*<<< orphan*/ *) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__ shared ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void configCommand(client *c) {
    if (!strcasecmp(c->argv[1]->ptr,"set")) {
        if (c->argc != 4) goto badarity;
        configSetCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"get")) {
        if (c->argc != 3) goto badarity;
        configGetCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"resetstat")) {
        if (c->argc != 2) goto badarity;
        resetServerStats();
        resetCommandTableStats();
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"rewrite")) {
        if (c->argc != 2) goto badarity;
        if (server.configfile == NULL) {
            addReplyError(c,"The server is running without a config file");
            return;
        }
        if (rewriteConfig(server.configfile) == -1) {
            serverLog(LL_WARNING,"CONFIG REWRITE failed: %s", strerror(errno));
            addReplyErrorFormat(c,"Rewriting config file: %s", strerror(errno));
        } else {
            serverLog(LL_WARNING,"CONFIG REWRITE executed with success.");
            addReply(c,shared.ok);
        }
    } else {
        addReplyError(c,
            "CONFIG subcommand must be one of GET, SET, RESETSTAT, REWRITE");
    }
    return;

badarity:
    addReplyErrorFormat(c,"Wrong number of arguments for CONFIG %s",
        (char*) c->argv[1]->ptr);
}