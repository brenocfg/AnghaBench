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
struct serverCommand {int /*<<< orphan*/  keystep; int /*<<< orphan*/  lastkey; int /*<<< orphan*/  firstkey; int /*<<< orphan*/  arity; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_2__ {int /*<<< orphan*/  nullbulk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ADMIN ; 
 int /*<<< orphan*/  CMD_DENYOOM ; 
 int /*<<< orphan*/  CMD_FAST ; 
 int /*<<< orphan*/  CMD_LOADING ; 
 int /*<<< orphan*/  CMD_RANDOM ; 
 int /*<<< orphan*/  CMD_READONLY ; 
 int /*<<< orphan*/  CMD_SKIP_MONITOR ; 
 int /*<<< orphan*/  CMD_WRITE ; 
 void* addDeferredMultiBulkLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ addReplyCommandFlag (int /*<<< orphan*/ *,struct serverCommand*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyMultiBulkLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setDeferredMultiBulkLength (int /*<<< orphan*/ *,void*,int) ; 
 TYPE_1__ shared ; 

void addReplyCommand(client *c, struct serverCommand *cmd) {
    if (!cmd) {
        addReply(c, shared.nullbulk);
    } else {
        /* We are adding: command name, arg count, flags, first, last, offset */
        addReplyMultiBulkLen(c, 6);
        addReplyBulkCString(c, cmd->name);
        addReplyLongLong(c, cmd->arity);

        int flagcount = 0;
        void *flaglen = addDeferredMultiBulkLength(c);
        flagcount += addReplyCommandFlag(c,cmd,CMD_WRITE, "write");
        flagcount += addReplyCommandFlag(c,cmd,CMD_READONLY, "readonly");
        flagcount += addReplyCommandFlag(c,cmd,CMD_DENYOOM, "denyoom");
        flagcount += addReplyCommandFlag(c,cmd,CMD_ADMIN, "admin");
        flagcount += addReplyCommandFlag(c,cmd,CMD_RANDOM, "random");
        flagcount += addReplyCommandFlag(c,cmd,CMD_LOADING, "loading");
        flagcount += addReplyCommandFlag(c,cmd,CMD_SKIP_MONITOR, "skip_monitor");
        flagcount += addReplyCommandFlag(c,cmd,CMD_FAST, "fast");
        setDeferredMultiBulkLength(c, flaglen, flagcount);

        addReplyLongLong(c, cmd->firstkey);
        addReplyLongLong(c, cmd->lastkey);
        addReplyLongLong(c, cmd->keystep);
    }
}