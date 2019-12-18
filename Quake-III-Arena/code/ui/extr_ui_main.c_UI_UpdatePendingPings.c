#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ realTime; } ;
struct TYPE_5__ {scalar_t__ refreshtime; int /*<<< orphan*/  refreshActive; } ;
struct TYPE_8__ {TYPE_2__ uiDC; TYPE_1__ serverStatus; } ;
struct TYPE_7__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_LAN_ResetPings (int /*<<< orphan*/ ) ; 
 TYPE_4__ uiInfo ; 
 TYPE_3__ ui_netSource ; 

__attribute__((used)) static void UI_UpdatePendingPings() { 
	trap_LAN_ResetPings(ui_netSource.integer);
	uiInfo.serverStatus.refreshActive = qtrue;
	uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 1000;

}