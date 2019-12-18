#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_6__* cmd; int /*<<< orphan*/  authenticated; int /*<<< orphan*/  argc; TYPE_1__** argv; TYPE_6__* lastcmd; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ client ;
struct TYPE_15__ {char* name; scalar_t__ proc; int flags; int /*<<< orphan*/  arity; } ;
struct TYPE_14__ {int aof_last_write_status; scalar_t__ loading; int /*<<< orphan*/  aof_last_write_errno; scalar_t__ maxmemory; scalar_t__ requirepass; } ;
struct TYPE_13__ {int /*<<< orphan*/  loadingerr; int /*<<< orphan*/  oomerr; int /*<<< orphan*/  noautherr; int /*<<< orphan*/  ok; } ;
struct TYPE_11__ {scalar_t__ ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_CLOSE_AFTER_REPLY ; 
 int /*<<< orphan*/  CMD_CALL_FULL ; 
 int CMD_DENYOOM ; 
 int CMD_LOADING ; 
 int CMD_WRITE ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  addReplySds (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ authCommand ; 
 int /*<<< orphan*/  call (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int freeMemoryIfNeeded () ; 
 int /*<<< orphan*/  handleClientsBlockedOnQueues () ; 
 TYPE_6__* lookupCommand (scalar_t__) ; 
 scalar_t__ pingCommand ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 TYPE_4__ server ; 
 TYPE_3__ shared ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int processCommand(client *c) {
    /* The QUIT command is handled separately. Normal command procs will
     * go through checking for replication and QUIT will cause trouble
     * when FORCE_REPLICATION is enabled and would be implemented in
     * a regular command proc. */
    if (!strcasecmp(c->argv[0]->ptr,"quit")) {
        addReply(c,shared.ok);
        c->flags |= CLIENT_CLOSE_AFTER_REPLY;
        return C_ERR;
    }

    /* Now lookup the command and check ASAP about trivial error conditions
     * such as wrong arity, bad command name and so forth. */
    c->cmd = c->lastcmd = lookupCommand(c->argv[0]->ptr);
    if (!c->cmd) {
        addReplyErrorFormat(c,"unknown command '%s'",
            (char*)c->argv[0]->ptr);
        return C_OK;
    } else if ((c->cmd->arity > 0 && c->cmd->arity != c->argc) ||
               (c->argc < -c->cmd->arity)) {
        addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
            c->cmd->name);
        return C_OK;
    }

    /* Check if the user is authenticated */
    if (server.requirepass && !c->authenticated && c->cmd->proc != authCommand)
    {
        addReply(c,shared.noautherr);
        return C_OK;
    }

    /* Handle the maxmemory directive.
     *
     * First we try to free some memory if possible (if there are volatile
     * keys in the dataset). If there are not the only thing we can do
     * is returning an error. */
    if (server.maxmemory) {
        int retval = freeMemoryIfNeeded();
        if ((c->cmd->flags & CMD_DENYOOM) && retval == C_ERR) {
            addReply(c, shared.oomerr);
            return C_OK;
        }
    }

    /* Don't accept write commands if there are problems persisting on disk. */
    if (server.aof_last_write_status == C_ERR &&
         (c->cmd->flags & CMD_WRITE ||
          c->cmd->proc == pingCommand))
    {
        addReplySds(c,
            sdscatprintf(sdsempty(),
            "-MISCONF Errors writing to the AOF file: %s\r\n",
            strerror(server.aof_last_write_errno)));
        return C_OK;
    }

    /* Loading DB? Return an error if the command has not the
     * CMD_LOADING flag. */
    if (server.loading && !(c->cmd->flags & CMD_LOADING)) {
        addReply(c, shared.loadingerr);
        return C_OK;
    }

    call(c,CMD_CALL_FULL);
    handleClientsBlockedOnQueues();
    return C_OK;
}