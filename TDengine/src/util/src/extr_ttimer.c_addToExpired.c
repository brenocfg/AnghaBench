#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {uintptr_t id; int /*<<< orphan*/  param; int /*<<< orphan*/  fp; TYPE_1__* ctrl; struct TYPE_7__* next; } ;
typedef  TYPE_2__ tmr_obj_t ;
struct TYPE_8__ {int /*<<< orphan*/ * thandle; TYPE_2__* ahandle; int /*<<< orphan*/  tfp; int /*<<< orphan*/ * fp; } ;
struct TYPE_6__ {int /*<<< orphan*/  label; } ;
typedef  TYPE_3__ SSchedMsg ;

/* Variables and functions */
 int /*<<< orphan*/  processExpiredTimer ; 
 int /*<<< orphan*/  taosScheduleTask (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  tmrQhandle ; 
 int /*<<< orphan*/  tmrTrace (char const*,uintptr_t,...) ; 

__attribute__((used)) static void addToExpired(tmr_obj_t* head) {
  const char* fmt = "%s adding expired timer[id=%lld, fp=%p, param=%p] to queue.";

  while (head != NULL) {
    uintptr_t id = head->id;
    tmr_obj_t* next = head->next;
    tmrTrace(fmt, head->ctrl->label, id, head->fp, head->param);

    SSchedMsg  schedMsg;
    schedMsg.fp = NULL;
    schedMsg.tfp = processExpiredTimer;
    schedMsg.ahandle = head;
    schedMsg.thandle = NULL;
    taosScheduleTask(tmrQhandle, &schedMsg);

    tmrTrace("timer[id=%lld] has been added to queue.", id);
    head = next;
  }
}