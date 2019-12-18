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
struct TYPE_3__ {char* msg; } ;
typedef  TYPE_1__ SSchedMsg ;

/* Variables and functions */
 int /*<<< orphan*/  dTrace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * taosMsg ; 
 int /*<<< orphan*/  vnodeProcessMsgFromMgmt (char*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 

void vnodeProcessMsgFromMgmtSpec(SSchedMsg *sched) {
  char  msgType = *sched->msg;
  char *content = sched->msg + 1;

  dTrace("msg:%s is received from mgmt", taosMsg[msgType]);

  vnodeProcessMsgFromMgmt(content, 0, msgType, 0);

  free(sched->msg);
}