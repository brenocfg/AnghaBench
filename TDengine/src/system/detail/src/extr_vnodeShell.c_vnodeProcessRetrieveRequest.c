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
struct TYPE_3__ {char* msg; int /*<<< orphan*/  fp; int /*<<< orphan*/ * ahandle; } ;
typedef  int /*<<< orphan*/  SShellObj ;
typedef  TYPE_1__ SSchedMsg ;

/* Variables and functions */
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  queryQhandle ; 
 int /*<<< orphan*/  taosScheduleTask (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vnodeExecuteRetrieveReq ; 

int vnodeProcessRetrieveRequest(char *pMsg, int msgLen, SShellObj *pObj) {
  SSchedMsg schedMsg;

  char *msg = malloc(msgLen);
  memcpy(msg, pMsg, msgLen);
  schedMsg.msg = msg;
  schedMsg.ahandle = pObj;
  schedMsg.fp = vnodeExecuteRetrieveReq;
  taosScheduleTask(queryQhandle, &schedMsg);

  return msgLen;
}