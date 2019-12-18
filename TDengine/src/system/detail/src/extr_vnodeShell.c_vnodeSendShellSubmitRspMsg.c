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
typedef  int /*<<< orphan*/  numOfPoints ;
typedef  int int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  thandle; } ;
typedef  TYPE_1__ SShellObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_SUBMIT_RSP ; 
 char* taosBuildRspMsgWithSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taosSendMsgToPeer (int /*<<< orphan*/ ,char*,int) ; 

int vnodeSendShellSubmitRspMsg(SShellObj *pObj, int code, int numOfPoints) {
  char *pMsg, *pStart;
  int   msgLen;

  pStart = taosBuildRspMsgWithSize(pObj->thandle, TSDB_MSG_TYPE_SUBMIT_RSP, 128);
  if (pStart == NULL) return -1;
  pMsg = pStart;

  *pMsg = code;
  pMsg++;

  *(int32_t *)pMsg = numOfPoints;
  pMsg += sizeof(numOfPoints);

  msgLen = pMsg - pStart;
  taosSendMsgToPeer(pObj->thandle, pStart, msgLen);

  return msgLen;
}