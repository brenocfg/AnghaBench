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
typedef  int /*<<< orphan*/  SMgmtObj ;

/* Variables and functions */
 char* taosBuildRspMsgToMnode (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  taosSendMsgToMnode (int /*<<< orphan*/ ,char*,char) ; 

int taosSendSimpleRspToMnode(SMgmtObj *pObj, char rsptype, char code) {
  char *pStart = taosBuildRspMsgToMnode(0, rsptype);
  if (pStart == NULL) {
    return 0;
  }

  *pStart = code;
  taosSendMsgToMnode(0, pStart, code);

  return 0;
}