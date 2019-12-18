#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  cbcrWrPmStats1; int /*<<< orphan*/  cbcrWrPmStats0; int /*<<< orphan*/  yWrPmStats1; int /*<<< orphan*/  yWrPmStats0; } ;
struct TYPE_7__ {int /*<<< orphan*/  cbcrWrPmStats1; int /*<<< orphan*/  cbcrWrPmStats0; int /*<<< orphan*/  yWrPmStats1; int /*<<< orphan*/  yWrPmStats0; } ;
struct TYPE_10__ {TYPE_4__ viewPathPmInfo; TYPE_2__ encPathPmInfo; } ;
struct vfe_irq_thread_msg {TYPE_5__ pmInfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  cbcrWrPmStats1; int /*<<< orphan*/  cbcrWrPmStats0; int /*<<< orphan*/  yWrPmStats1; int /*<<< orphan*/  yWrPmStats0; } ;
struct TYPE_6__ {int /*<<< orphan*/  cbcrWrPmStats1; int /*<<< orphan*/  cbcrWrPmStats0; int /*<<< orphan*/  yWrPmStats1; int /*<<< orphan*/  yWrPmStats0; } ;
struct vfe_bus_performance_monitor {TYPE_3__ viewPathPmInfo; TYPE_1__ encPathPmInfo; } ;
typedef  int /*<<< orphan*/  rc ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vfe_bus_performance_monitor*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct vfe_bus_performance_monitor
vfe_get_performance_monitor_data(struct vfe_irq_thread_msg *in)
{
	struct vfe_bus_performance_monitor rc;
	memset(&rc, 0, sizeof(rc));

	rc.encPathPmInfo.yWrPmStats0     =
		in->pmInfo.encPathPmInfo.yWrPmStats0;
	rc.encPathPmInfo.yWrPmStats1     =
		in->pmInfo.encPathPmInfo.yWrPmStats1;
	rc.encPathPmInfo.cbcrWrPmStats0  =
		in->pmInfo.encPathPmInfo.cbcrWrPmStats0;
	rc.encPathPmInfo.cbcrWrPmStats1  =
		in->pmInfo.encPathPmInfo.cbcrWrPmStats1;
	rc.viewPathPmInfo.yWrPmStats0    =
		in->pmInfo.viewPathPmInfo.yWrPmStats0;
	rc.viewPathPmInfo.yWrPmStats1    =
		in->pmInfo.viewPathPmInfo.yWrPmStats1;
	rc.viewPathPmInfo.cbcrWrPmStats0 =
		in->pmInfo.viewPathPmInfo.cbcrWrPmStats0;
	rc.viewPathPmInfo.cbcrWrPmStats1 =
		in->pmInfo.viewPathPmInfo.cbcrWrPmStats1;

	return rc;
}