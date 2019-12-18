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
struct TYPE_2__ {int /*<<< orphan*/ * timer; int /*<<< orphan*/ * initTimer; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_STATE_STOPPED ; 
 TYPE_1__* monitor ; 
 int /*<<< orphan*/  monitorLPrint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taosLogFp ; 
 int /*<<< orphan*/  taosTmrStopA (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tsInternalIp ; 
 int /*<<< orphan*/  tsPrivateIp ; 

void monitorStopSystem() {
  if (monitor == NULL) {
    return;
  }

#ifdef CLUSTER
  monitorLPrint("dnode:%s is stopped", tsPrivateIp);
#else
  monitorLPrint("dnode:%s is stopped", tsInternalIp);
#endif
  monitor->state = MONITOR_STATE_STOPPED;
  taosLogFp = NULL;
  if (monitor->initTimer != NULL) {
    taosTmrStopA(&(monitor->initTimer));
  }
  if (monitor->timer != NULL) {
    taosTmrStopA(&(monitor->timer));
  }
}