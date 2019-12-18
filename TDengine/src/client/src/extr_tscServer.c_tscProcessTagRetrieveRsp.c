#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_11__ {scalar_t__ functionId; } ;
struct TYPE_10__ {TYPE_1__* pMetricMeta; } ;
struct TYPE_9__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_8__ {int numOfMeters; } ;
typedef  TYPE_2__ SSqlObj ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_3__ SMeterMetaInfo ;

/* Variables and functions */
 scalar_t__ TSDB_FUNC_TAGPRJ ; 
 TYPE_3__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tscLocalResultCommonBuilder (TYPE_2__*,int) ; 
 TYPE_4__* tscSqlExprGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int tscProcessTagRetrieveRsp(SSqlObj *pSql) {
  SSqlCmd *       pCmd = &pSql->cmd;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  int32_t numOfRes = 0;
  if (tscSqlExprGet(pCmd, 0)->functionId == TSDB_FUNC_TAGPRJ) {
    numOfRes = pMeterMetaInfo->pMetricMeta->numOfMeters;
  } else {
    numOfRes = 1;  // for count function, there is only one output.
  }
  return tscLocalResultCommonBuilder(pSql, numOfRes);
}