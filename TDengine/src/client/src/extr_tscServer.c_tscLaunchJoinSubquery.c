#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_9__ ;
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_23__ ;
typedef  struct TYPE_40__   TYPE_22__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_12__ ;
typedef  struct TYPE_37__   TYPE_11__ ;
typedef  struct TYPE_36__   TYPE_10__ ;

/* Type definitions */
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_49__ {TYPE_3__* pMeterMeta; } ;
struct TYPE_48__ {int bytes; int /*<<< orphan*/  type; } ;
struct TYPE_40__ {size_t numOfCols; int /*<<< orphan*/ * pColList; } ;
struct TYPE_47__ {int /*<<< orphan*/  type; TYPE_22__ colList; int /*<<< orphan*/  groupbyExpr; int /*<<< orphan*/  limit; scalar_t__ nAggTimeInterval; scalar_t__ numOfCols; int /*<<< orphan*/  tagCond; int /*<<< orphan*/  fieldsInfo; int /*<<< orphan*/  exprsInfo; } ;
struct TYPE_46__ {int numOfParams; TYPE_4__* param; } ;
struct TYPE_39__ {int qhandle; scalar_t__ numOfRows; } ;
struct TYPE_45__ {TYPE_7__ cmd; int /*<<< orphan*/  numOfSubs; struct TYPE_45__** pSubs; TYPE_1__ res; } ;
struct TYPE_44__ {int /*<<< orphan*/  i64Key; } ;
struct TYPE_43__ {int /*<<< orphan*/  uid; } ;
struct TYPE_42__ {int numOfTotal; } ;
struct TYPE_41__ {size_t numOfCols; TYPE_12__* pColList; } ;
struct TYPE_38__ {scalar_t__ numOfFilters; } ;
struct TYPE_37__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_36__ {TYPE_23__ colList; int /*<<< orphan*/  groupbyExpr; int /*<<< orphan*/  tagCond; int /*<<< orphan*/  fieldsInfo; int /*<<< orphan*/  uid; int /*<<< orphan*/  exprsInfo; TYPE_2__* pState; } ;
typedef  TYPE_5__ SSqlObj ;
typedef  int /*<<< orphan*/  SSqlGroupbyExpr ;
typedef  TYPE_6__ SSqlExpr ;
typedef  TYPE_7__ SSqlCmd ;
typedef  TYPE_8__ SSchema ;
typedef  TYPE_9__ SMeterMetaInfo ;
typedef  int /*<<< orphan*/  SLimitVal ;
typedef  TYPE_10__ SJoinSubquerySupporter ;
typedef  TYPE_11__ SColumnIndex ;
typedef  TYPE_12__ SColumnBase ;

/* Variables and functions */
 int POINTER_BYTES ; 
 int /*<<< orphan*/  PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 scalar_t__ QUERY_IS_JOIN_QUERY (int /*<<< orphan*/ ) ; 
 size_t TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  TSDB_COL_NORMAL ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_BINARY ; 
 int /*<<< orphan*/  TSDB_FUNC_TS_COMP ; 
 int /*<<< orphan*/  TSDB_QUERY_TYPE_SUBQUERY ; 
 int /*<<< orphan*/  addGroupInfoForSubquery (TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addRequiredTagColumn (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* createSubqueryObj (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ *) ; 
 TYPE_5__** malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tscAddSpecialColumnForSelect (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscColumnBaseCopy (int /*<<< orphan*/ *,TYPE_12__*) ; 
 int /*<<< orphan*/  tscColumnBaseInfoCopy (TYPE_23__*,TYPE_22__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscColumnBaseInfoUpdateTableIndex (TYPE_22__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscFieldInfoCopyAll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscFreeSqlCmdData (TYPE_7__*) ; 
 int /*<<< orphan*/  tscGetJoinTagColIndexByUid (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* tscGetMeterMetaInfo (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscJoinQueryCallback ; 
 size_t tscProcessSql (TYPE_5__*) ; 
 int /*<<< orphan*/  tscSqlExprCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* tscSqlExprGet (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscTagCondCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int32_t tscLaunchJoinSubquery(SSqlObj *pSql, int16_t tableIndex, int16_t vnodeIdx, SJoinSubquerySupporter *pSupporter) {
  SSqlCmd *pCmd = &pSql->cmd;

  pSql->res.qhandle = 0x1;
  pSql->res.numOfRows = 0;

  if (pSql->pSubs == NULL) {
    pSql->pSubs = malloc(POINTER_BYTES * pSupporter->pState->numOfTotal);
    if (pSql->pSubs == NULL) {
      return TSDB_CODE_CLI_OUT_OF_MEMORY;
    }
  }

  SSqlObj *pNew = createSubqueryObj(pSql, vnodeIdx, tableIndex, tscJoinQueryCallback, pSupporter, NULL);
  if (pNew == NULL) {
    return TSDB_CODE_CLI_OUT_OF_MEMORY;
  }

  pSql->pSubs[pSql->numOfSubs++] = pNew;

  if (QUERY_IS_JOIN_QUERY(pCmd->type)) {
    addGroupInfoForSubquery(pSql, pNew, tableIndex);

    // refactor as one method
    tscColumnBaseInfoUpdateTableIndex(&pNew->cmd.colList, 0);
    tscColumnBaseInfoCopy(&pSupporter->colList, &pNew->cmd.colList, 0);

    tscSqlExprCopy(&pSupporter->exprsInfo, &pNew->cmd.exprsInfo, pSupporter->uid);

    tscFieldInfoCopyAll(&pNew->cmd.fieldsInfo, &pSupporter->fieldsInfo);
    tscTagCondCopy(&pSupporter->tagCond, &pNew->cmd.tagCond);
    pSupporter->groupbyExpr = pNew->cmd.groupbyExpr;

    pNew->cmd.numOfCols = 0;
    pNew->cmd.nAggTimeInterval = 0;
    memset(&pNew->cmd.limit, 0, sizeof(SLimitVal));
    memset(&pNew->cmd.groupbyExpr, 0, sizeof(SSqlGroupbyExpr));

    // set the ts,tags that involved in join, as the output column of intermediate result
    tscFreeSqlCmdData(&pNew->cmd);

    SSchema      colSchema = {.type = TSDB_DATA_TYPE_BINARY, .bytes = 1};
    SColumnIndex index = {0, PRIMARYKEY_TIMESTAMP_COL_INDEX};

    tscAddSpecialColumnForSelect(&pNew->cmd, 0, TSDB_FUNC_TS_COMP, &index, &colSchema, TSDB_COL_NORMAL);

    // set the tags value for ts_comp function
    SSqlExpr *pExpr = tscSqlExprGet(&pNew->cmd, 0);

    SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(&pNew->cmd, 0);
    int16_t         tagColIndex = tscGetJoinTagColIndexByUid(&pNew->cmd, pMeterMetaInfo->pMeterMeta->uid);

    pExpr->param->i64Key = tagColIndex;
    pExpr->numOfParams = 1;

    addRequiredTagColumn(pCmd, tagColIndex, 0);

    // add the filter tag column
    for (int32_t i = 0; i < pSupporter->colList.numOfCols; ++i) {
      SColumnBase *pColBase = &pSupporter->colList.pColList[i];
      if (pColBase->numOfFilters > 0) {  // copy to the pNew->cmd.colList if it is filtered.
        tscColumnBaseCopy(&pNew->cmd.colList.pColList[pNew->cmd.colList.numOfCols], pColBase);
        pNew->cmd.colList.numOfCols++;
      }
    }
  } else {
    pNew->cmd.type |= TSDB_QUERY_TYPE_SUBQUERY;
  }

  return tscProcessSql(pNew);
}