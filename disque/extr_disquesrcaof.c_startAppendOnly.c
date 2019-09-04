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
struct TYPE_2__ {int aof_fd; scalar_t__ aof_state; int /*<<< orphan*/  aof_filename; int /*<<< orphan*/  unixtime; int /*<<< orphan*/  aof_last_fsync; } ;

/* Variables and functions */
 scalar_t__ AOF_OFF ; 
 scalar_t__ AOF_WAIT_REWRITE ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int rewriteAppendOnlyFileBackground () ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int startAppendOnly(void) {
    server.aof_last_fsync = server.unixtime;
    server.aof_fd = open(server.aof_filename,O_WRONLY|O_APPEND|O_CREAT,0644);
    serverAssert(server.aof_state == AOF_OFF);
    if (server.aof_fd == -1) {
        serverLog(LL_WARNING,"Disque needs to enable the AOF but can't open the append only file: %s",strerror(errno));
        return C_ERR;
    }
    if (rewriteAppendOnlyFileBackground() == C_ERR) {
        close(server.aof_fd);
        serverLog(LL_WARNING,"Disque needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
        return C_ERR;
    }
    /* We correctly switched on AOF, now wait for the rewrite to be complete
     * in order to append data on disk. */
    server.aof_state = AOF_WAIT_REWRITE;
    return C_OK;
}