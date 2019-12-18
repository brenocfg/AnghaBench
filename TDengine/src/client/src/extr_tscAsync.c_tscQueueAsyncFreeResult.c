#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * msg; void* thandle; int /*<<< orphan*/ * ahandle; int /*<<< orphan*/  fp; } ;
typedef  int /*<<< orphan*/  SSqlObj ;
typedef  TYPE_1__ SSchedMsg ;

/* Variables and functions */
 int /*<<< orphan*/  taosScheduleTask (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  tscProcessAsyncFree ; 
 int /*<<< orphan*/  tscQhandle ; 
 int /*<<< orphan*/  tscTrace (char*,int /*<<< orphan*/ *) ; 

void tscQueueAsyncFreeResult(SSqlObj *pSql) {
  tscTrace("%p sqlObj put in queue to async free", pSql);

  SSchedMsg schedMsg;
  schedMsg.fp = tscProcessAsyncFree;
  schedMsg.ahandle = pSql;
  schedMsg.thandle = (void *)1;
  schedMsg.msg = NULL;
  taosScheduleTask(tscQhandle, &schedMsg);
}