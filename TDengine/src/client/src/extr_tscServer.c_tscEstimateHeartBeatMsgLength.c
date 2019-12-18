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
struct TYPE_7__ {struct TYPE_7__* next; TYPE_1__* pTscObj; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__* streamList; TYPE_3__* sqlList; } ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlStream ;
typedef  TYPE_3__ SSqlObj ;
typedef  int /*<<< orphan*/  SSList ;
typedef  int /*<<< orphan*/  SSDesc ;
typedef  int /*<<< orphan*/  SQList ;
typedef  int /*<<< orphan*/  SQDesc ;
typedef  int /*<<< orphan*/  SMgmtHead ;

/* Variables and functions */
 int TSDB_EXTRA_PAYLOAD_SIZE ; 
 scalar_t__ tsRpcHeadSize ; 

int tscEstimateHeartBeatMsgLength(SSqlObj *pSql) {
  int      size = 0;
  STscObj *pObj = pSql->pTscObj;

  size += tsRpcHeadSize + sizeof(SMgmtHead);
  size += sizeof(SQList);

  SSqlObj *tpSql = pObj->sqlList;
  while (tpSql) {
    size += sizeof(SQDesc);
    tpSql = tpSql->next;
  }

  size += sizeof(SSList);
  SSqlStream *pStream = pObj->streamList;
  while (pStream) {
    size += sizeof(SSDesc);
    pStream = pStream->next;
  }

  return size + TSDB_EXTRA_PAYLOAD_SIZE;
}