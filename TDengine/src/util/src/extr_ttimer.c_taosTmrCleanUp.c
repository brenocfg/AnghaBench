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
struct TYPE_3__ {scalar_t__* label; struct TYPE_3__* next; } ;
typedef  TYPE_1__ tmr_ctrl_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  numOfTmrCtrl ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmrCtrlMutex ; 
 int /*<<< orphan*/  tmrTrace (char*,scalar_t__*) ; 
 TYPE_1__* unusedTmrCtrl ; 

void taosTmrCleanUp(void* handle) {
  tmr_ctrl_t* ctrl = (tmr_ctrl_t*)handle;
  assert(ctrl != NULL && ctrl->label[0] != 0);

  tmrTrace("%s timer controller is cleaned up.", ctrl->label);
  ctrl->label[0] = 0;

  pthread_mutex_lock(&tmrCtrlMutex);
  ctrl->next = unusedTmrCtrl;
  numOfTmrCtrl--;
  unusedTmrCtrl = ctrl;
  pthread_mutex_unlock(&tmrCtrlMutex);
}