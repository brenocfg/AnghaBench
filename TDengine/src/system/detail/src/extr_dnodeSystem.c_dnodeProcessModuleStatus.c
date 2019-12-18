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
typedef  void* uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* startFp ) () ;int /*<<< orphan*/  name; int /*<<< orphan*/  (* stopFp ) () ;} ;

/* Variables and functions */
 int TSDB_MOD_MAX ; 
 int /*<<< orphan*/  dPrint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 scalar_t__ tsDnodeStopping ; 
 TYPE_1__* tsModule ; 
 int tsModuleStatus ; 

void dnodeProcessModuleStatus(uint32_t status) {
  if (tsDnodeStopping) return;

  int news = status;
  int olds = tsModuleStatus;

  for (int moduleType = 0; moduleType < TSDB_MOD_MAX; ++moduleType) {
    int newStatus = news & (1 << moduleType);
    int oldStatus = olds & (1 << moduleType);

    if (oldStatus > 0) {
      if (newStatus == 0) {
        if (tsModule[moduleType].stopFp) {
          dPrint("module:%s is stopped on this node", tsModule[moduleType].name);
          (*tsModule[moduleType].stopFp)();
        }
      }
    } else if (oldStatus == 0) {
      if (newStatus > 0) {
        if (tsModule[moduleType].startFp) {
          dPrint("module:%s is started on this node", tsModule[moduleType].name);
          (*tsModule[moduleType].startFp)();
        }
      }
    } else {
    }
  }
  tsModuleStatus = status;
}