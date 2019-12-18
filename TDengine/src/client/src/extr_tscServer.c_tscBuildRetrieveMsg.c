#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {char* payload; int payloadLen; int /*<<< orphan*/  msgType; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  qhandle; } ;
struct TYPE_7__ {TYPE_2__ cmd; TYPE_1__ res; } ;
typedef  TYPE_3__ SSqlObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_MSG_TYPE_RETRIEVE ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int tsRpcHeadSize ; 

int tscBuildRetrieveMsg(SSqlObj *pSql) {
  char *pMsg, *pStart;
  int   msgLen = 0;

  pStart = pSql->cmd.payload + tsRpcHeadSize;
  pMsg = pStart;

  *((uint64_t *)pMsg) = pSql->res.qhandle;
  pMsg += sizeof(pSql->res.qhandle);

  *((uint16_t*)pMsg) = htons(pSql->cmd.type);
  pMsg += sizeof(pSql->cmd.type);

  msgLen = pMsg - pStart;
  pSql->cmd.payloadLen = msgLen;
  pSql->cmd.msgType = TSDB_MSG_TYPE_RETRIEVE;

  return msgLen;
}