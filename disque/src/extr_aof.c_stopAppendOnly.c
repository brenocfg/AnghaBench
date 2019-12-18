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
struct TYPE_2__ {scalar_t__ aof_state; int aof_fd; int aof_selected_db; int aof_child_pid; int aof_rewrite_time_start; } ;

/* Variables and functions */
 scalar_t__ AOF_OFF ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  aofClosePipes () ; 
 int /*<<< orphan*/  aofRemoveTempFile (int) ; 
 int /*<<< orphan*/  aofRewriteBufferReset () ; 
 int /*<<< orphan*/  aof_fsync (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  flushAppendOnlyFile (int) ; 
 int kill (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  wait3 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void stopAppendOnly(void) {
    serverAssert(server.aof_state != AOF_OFF);
    flushAppendOnlyFile(1);
    aof_fsync(server.aof_fd);
    close(server.aof_fd);

    server.aof_fd = -1;
    server.aof_selected_db = -1;
    server.aof_state = AOF_OFF;
    /* rewrite operation in progress? kill it, wait child exit */
    if (server.aof_child_pid != -1) {
        int statloc;

        serverLog(LL_NOTICE,"Killing running AOF rewrite child: %ld",
            (long) server.aof_child_pid);
        if (kill(server.aof_child_pid,SIGUSR1) != -1)
            wait3(&statloc,0,NULL);
        /* reset the buffer accumulating changes while the child saves */
        aofRewriteBufferReset();
        aofRemoveTempFile(server.aof_child_pid);
        server.aof_child_pid = -1;
        server.aof_rewrite_time_start = -1;
        /* close pipes used for IPC between the two processes. */
        aofClosePipes();
    }
}