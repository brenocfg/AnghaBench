#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_5__* pMeterMeta; } ;
struct TYPE_17__ {scalar_t__ numOfTags; scalar_t__ numOfColumns; } ;
struct TYPE_16__ {int /*<<< orphan*/  payload; } ;
struct TYPE_15__ {scalar_t__ functionId; } ;
struct TYPE_13__ {int code; } ;
struct TYPE_14__ {TYPE_1__ res; TYPE_4__ cmd; } ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlExpr ;
typedef  TYPE_4__ SSqlCmd ;
typedef  TYPE_5__ SMeterMeta ;

/* Variables and functions */
 int TSDB_CODE_INVALID_TABLE ; 
 scalar_t__ TSDB_FUNC_COUNT ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int tscBuildMetricTagProjectionResult (TYPE_2__*) ; 
 int tscBuildMetricTagSqlFunctionResult (TYPE_2__*) ; 
 TYPE_9__* tscGetMeterMetaInfo (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tscSqlExprGet (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tscProcessQueryTags(SSqlObj *pSql) {
  SSqlCmd *pCmd = &pSql->cmd;

  SMeterMeta *pMeterMeta = tscGetMeterMetaInfo(pCmd, 0)->pMeterMeta;
  if (pMeterMeta == NULL || pMeterMeta->numOfTags == 0 || pMeterMeta->numOfColumns == 0) {
    strcpy(pCmd->payload, "invalid table");
    pSql->res.code = TSDB_CODE_INVALID_TABLE;
    return pSql->res.code;
  }

  SSqlExpr *pExpr = tscSqlExprGet(pCmd, 0);
  if (pExpr->functionId == TSDB_FUNC_COUNT) {
    return tscBuildMetricTagSqlFunctionResult(pSql);
  } else {
    return tscBuildMetricTagProjectionResult(pSql);
  }
}