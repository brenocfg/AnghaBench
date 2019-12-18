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
struct TYPE_3__ {char* msg; int /*<<< orphan*/ * thandle; int /*<<< orphan*/ * ahandle; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ SSchedMsg ;
typedef  int /*<<< orphan*/  SDnodeObj ;

/* Variables and functions */
 int /*<<< orphan*/  dmQhandle ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taosMsg ; 
 int /*<<< orphan*/  taosScheduleTask (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vnodeProcessMsgFromMgmtSpec ; 

int taosSendMsgToDnode(SDnodeObj *pObj, char *msg, int msgLen) {
  mTrace("msg:%s is sent to dnode", taosMsg[*(msg-1)]);

  /*
   * Lite version has no message header, so minus one
   */
  SSchedMsg schedMsg;
  schedMsg.fp = vnodeProcessMsgFromMgmtSpec;
  schedMsg.msg = msg - 1;
  schedMsg.ahandle = NULL;
  schedMsg.thandle = NULL;
  taosScheduleTask(dmQhandle, &schedMsg);

  return 0;
}