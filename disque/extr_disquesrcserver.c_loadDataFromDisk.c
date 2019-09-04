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
struct TYPE_2__ {scalar_t__ aof_state; scalar_t__ configfile; scalar_t__ aof_enqueue_jobs_once; int /*<<< orphan*/  aof_filename; } ;

/* Variables and functions */
 scalar_t__ AOF_ON ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ loadAppendOnlyFile (int /*<<< orphan*/ ) ; 
 int rewriteConfig (scalar_t__) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,float) ; 
 float strerror (int /*<<< orphan*/ ) ; 
 long long ustime () ; 

void loadDataFromDisk(void) {
    long long start = ustime();
    if (server.aof_state == AOF_ON || server.aof_enqueue_jobs_once) {
        if (loadAppendOnlyFile(server.aof_filename) == C_OK)
            serverLog(LL_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);

        /* Rewrite aof-enqueue-jobs-once setting it to no if enabled: this
         * option has the special property of auto-turning itself off. */
        if (server.aof_enqueue_jobs_once && server.configfile) {
            server.aof_enqueue_jobs_once = 0;
            if (rewriteConfig(server.configfile) == -1) {
                serverLog(LL_WARNING,
                    "CONFIG REWRITE failed "
                    "(executed to turn off aof-enqueue-jobs-once): %s",
                    strerror(errno));
            }
        }
    }
}