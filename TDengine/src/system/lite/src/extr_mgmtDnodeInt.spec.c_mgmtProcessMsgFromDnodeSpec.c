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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmtGetDnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmtProcessMsgFromDnode (char*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taosMsg ; 

void mgmtProcessMsgFromDnodeSpec(SSchedMsg *sched) {
  char  msgType = *sched->msg;
  char *content = sched->msg + 1;
  mTrace("msg:%s is received from dnode", taosMsg[msgType]);

  mgmtProcessMsgFromDnode(content, 0, msgType, mgmtGetDnode(0));
  free(sched->msg);
}