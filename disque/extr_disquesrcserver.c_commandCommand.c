#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_10__ {int argc; TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_11__ {int /*<<< orphan*/  commands; } ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyCommand (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,int) ; 
 int /*<<< orphan*/  addReplyMultiBulkLen (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int dictSize (int /*<<< orphan*/ ) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

void commandCommand(client *c) {
    dictIterator *di;
    dictEntry *de;

    if (c->argc == 1) {
        addReplyMultiBulkLen(c, dictSize(server.commands));
        di = dictGetIterator(server.commands);
        while ((de = dictNext(di)) != NULL) {
            addReplyCommand(c, dictGetVal(de));
        }
        dictReleaseIterator(di);
    } else if (!strcasecmp(c->argv[1]->ptr, "info")) {
        int i;
        addReplyMultiBulkLen(c, c->argc-2);
        for (i = 2; i < c->argc; i++) {
            addReplyCommand(c, dictFetchValue(server.commands, c->argv[i]->ptr));
        }
    } else if (!strcasecmp(c->argv[1]->ptr, "count") && c->argc == 2) {
        addReplyLongLong(c, dictSize(server.commands));
    } else {
        addReplyError(c, "Unknown subcommand or wrong number of arguments.");
        return;
    }
}