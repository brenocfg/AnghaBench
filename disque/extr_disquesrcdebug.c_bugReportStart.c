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
struct TYPE_2__ {int bug_report_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*) ; 

void bugReportStart(void) {
    if (server.bug_report_start == 0) {
        serverLog(LL_WARNING,
            "\n\n=== DISQUE BUG REPORT START: Cut & paste starting from here ===");
        server.bug_report_start = 1;
    }
}