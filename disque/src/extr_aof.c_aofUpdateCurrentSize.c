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
struct disque_stat {int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  mstime_t ;
struct TYPE_2__ {int /*<<< orphan*/  aof_current_size; int /*<<< orphan*/  aof_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 int disque_fstat (int /*<<< orphan*/ ,struct disque_stat*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  latencyAddSampleIfNeeded (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latencyEndMonitor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latencyStartMonitor (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void aofUpdateCurrentSize(void) {
    struct disque_stat sb;
    mstime_t latency;

    latencyStartMonitor(latency);
    if (disque_fstat(server.aof_fd,&sb) == -1) {
        serverLog(LL_WARNING,"Unable to obtain the AOF file length. stat: %s",
            strerror(errno));
    } else {
        server.aof_current_size = sb.st_size;
    }
    latencyEndMonitor(latency);
    latencyAddSampleIfNeeded("aof-fstat",latency);
}