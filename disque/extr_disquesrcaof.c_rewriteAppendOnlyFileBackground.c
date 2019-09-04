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
typedef  int pid_t ;
struct TYPE_2__ {int aof_child_pid; long long stat_fork_time; double stat_fork_rate; int aof_selected_db; int /*<<< orphan*/  aof_rewrite_time_start; scalar_t__ aof_rewrite_scheduled; } ;

/* Variables and functions */
 int C_ERR ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 scalar_t__ aofCreatePipes () ; 
 int /*<<< orphan*/  closeListeningSockets (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exitFromChild (int) ; 
 int fork () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  latencyAddSampleIfNeeded (char*,int) ; 
 scalar_t__ rewriteAppendOnlyFile (char*,int) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  serverSetProcTitle (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updateDictResizePolicy () ; 
 long long ustime () ; 
 size_t zmalloc_get_private_dirty () ; 
 scalar_t__ zmalloc_used_memory () ; 

int rewriteAppendOnlyFileBackground(void) {
    pid_t childpid;
    long long start;

    if (server.aof_child_pid != -1) return C_ERR;
    if (aofCreatePipes() != C_OK) return C_ERR;
    start = ustime();
    if ((childpid = fork()) == 0) {
        char tmpfile[256];

        /* Child */
        closeListeningSockets(0);
        serverSetProcTitle("disque-aof-rewrite");
        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
        if (rewriteAppendOnlyFile(tmpfile,1) == C_OK) {
            size_t private_dirty = zmalloc_get_private_dirty();

            if (private_dirty) {
                serverLog(LL_NOTICE,
                    "AOF rewrite: %zu MB of memory used by copy-on-write",
                    private_dirty/(1024*1024));
            }
            exitFromChild(0);
        } else {
            exitFromChild(1);
        }
    } else {
        /* Parent */
        server.stat_fork_time = ustime()-start;
        server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
        latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
        if (childpid == -1) {
            serverLog(LL_WARNING,
                "Can't rewrite append only file in background: fork: %s",
                strerror(errno));
            return C_ERR;
        }
        serverLog(LL_NOTICE,
            "Background append only file rewriting started by pid %d",childpid);
        server.aof_rewrite_scheduled = 0;
        server.aof_rewrite_time_start = time(NULL);
        server.aof_child_pid = childpid;
        updateDictResizePolicy();
        /* We set appendseldb to -1 in order to force the next call to the
         * feedAppendOnlyFile() to issue a SELECT command, so the differences
         * accumulated by the parent into server.aof_rewrite_buf will start
         * with a SELECT statement and it will be safe to merge. */
        server.aof_selected_db = -1;
        return C_OK;
    }
    return C_OK; /* unreached */
}