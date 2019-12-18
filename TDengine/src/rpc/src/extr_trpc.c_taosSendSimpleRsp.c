#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  tError (char*) ; 
 char* taosBuildRspMsgWithSize (void*,char,int) ; 
 int /*<<< orphan*/  taosSendMsgToPeer (void*,char*,int) ; 

int taosSendSimpleRsp(void *thandle, char rsptype, char code) {
  char *pMsg, *pStart;
  int   msgLen;

  if (thandle == NULL) {
    tError("connection is gone, response could not be sent");
    return -1;
  }

  pStart = taosBuildRspMsgWithSize(thandle, rsptype, 32);
  pMsg = pStart;

  *pMsg = code;
  pMsg++;

  msgLen = (int)(pMsg - pStart);
  taosSendMsgToPeer(thandle, pStart, msgLen);

  return msgLen;
}