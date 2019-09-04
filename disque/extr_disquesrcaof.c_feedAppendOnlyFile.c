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
typedef  scalar_t__ sds ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_2__ {scalar_t__ aof_state; int aof_child_pid; int /*<<< orphan*/  aof_buf; } ;

/* Variables and functions */
 scalar_t__ AOF_ON ; 
 int /*<<< orphan*/  aofRewriteBufferAppend (unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ catAppendOnlyGenericCommand (scalar_t__,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sdsempty () ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 TYPE_1__ server ; 

void feedAppendOnlyFile(robj **argv, int argc) {
    sds buf = sdsempty();

    buf = catAppendOnlyGenericCommand(buf,argc,argv);

    /* Append to the AOF buffer. This will be flushed on disk just before
     * of re-entering the event loop, so before the client will get a
     * positive reply about the operation performed. */
    if (server.aof_state == AOF_ON)
        server.aof_buf = sdscatlen(server.aof_buf,buf,sdslen(buf));

    /* If a background append only file rewriting is in progress we want to
     * accumulate the differences between the child DB and the current one
     * in a buffer, so that when the child process will do its work we
     * can append the differences to the new append only file. */
    if (server.aof_child_pid != -1)
        aofRewriteBufferAppend((unsigned char*)buf,sdslen(buf));

    sdsfree(buf);
}