#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_22__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_12__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
typedef  void* int32_t ;
typedef  size_t int16_t ;
struct TYPE_40__ {size_t type; size_t bytes; char* name; } ;
struct TYPE_36__ {scalar_t__ numOfGroupCols; TYPE_4__* columnInfo; } ;
struct TYPE_33__ {int /*<<< orphan*/  numOfOutputCols; } ;
struct TYPE_31__ {void* numOfExprs; } ;
struct TYPE_39__ {TYPE_5__ groupbyExpr; TYPE_2__ fieldsInfo; TYPE_1__ exprsInfo; } ;
struct TYPE_34__ {void* colIdx; int /*<<< orphan*/  flag; } ;
struct TYPE_38__ {scalar_t__ functionId; TYPE_3__ colInfo; } ;
struct TYPE_37__ {TYPE_8__ cmd; } ;
struct TYPE_35__ {void* colIdx; } ;
struct TYPE_32__ {int /*<<< orphan*/  uid; } ;
struct TYPE_30__ {size_t columnIndex; int /*<<< orphan*/  tableIndex; } ;
struct TYPE_29__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_28__ {TYPE_22__* pMeterMeta; } ;
typedef  TYPE_6__ SSqlObj ;
typedef  TYPE_7__ SSqlExpr ;
typedef  TYPE_8__ SSqlCmd ;
typedef  TYPE_9__ SSchema ;
typedef  TYPE_10__ SMeterMetaInfo ;
typedef  TYPE_11__ SColumnList ;
typedef  TYPE_12__ SColumnIndex ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_COL_TAG ; 
 scalar_t__ TSDB_FUNC_TAG ; 
 int /*<<< orphan*/  addRequiredTagColumn (TYPE_8__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insertResultField (TYPE_8__*,int /*<<< orphan*/ ,TYPE_11__*,size_t,size_t,char*) ; 
 TYPE_9__* tsGetTagSchema (TYPE_22__*) ; 
 size_t tscGetJoinTagColIndexByUid (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* tscGetMeterMetaInfo (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* tscSqlExprGet (TYPE_8__*,void*) ; 
 TYPE_7__* tscSqlExprInsert (TYPE_8__*,int /*<<< orphan*/ ,scalar_t__,TYPE_12__*,size_t,size_t,size_t) ; 

void addGroupInfoForSubquery(SSqlObj* pParentObj, SSqlObj* pSql, int32_t tableIndex) {
  if (pParentObj->cmd.groupbyExpr.numOfGroupCols > 0) {
    int32_t   num = pSql->cmd.exprsInfo.numOfExprs;
    SSqlExpr* pExpr = tscSqlExprGet(&pSql->cmd, num - 1);
    SSqlCmd*  pCmd = &pSql->cmd;

    if (pExpr->functionId != TSDB_FUNC_TAG) {
      SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(&pSql->cmd, 0);
      int16_t         columnInfo = tscGetJoinTagColIndexByUid(pCmd, pMeterMetaInfo->pMeterMeta->uid);
      SColumnIndex    index = {.tableIndex = 0, .columnIndex = columnInfo};
      SSchema*        pSchema = tsGetTagSchema(pMeterMetaInfo->pMeterMeta);

      int16_t type = pSchema[index.columnIndex].type;
      int16_t bytes = pSchema[index.columnIndex].bytes;
      char*   name = pSchema[index.columnIndex].name;

      pExpr = tscSqlExprInsert(pCmd, pCmd->fieldsInfo.numOfOutputCols, TSDB_FUNC_TAG, &index, type, bytes, bytes);
      pExpr->colInfo.flag = TSDB_COL_TAG;

      // NOTE: tag column does not add to source column list
      SColumnList ids = {0};
      insertResultField(pCmd, pCmd->fieldsInfo.numOfOutputCols, &ids, bytes, type, name);

      int32_t relIndex = index.columnIndex;

      pExpr->colInfo.colIdx = relIndex;
      pCmd->groupbyExpr.columnInfo[0].colIdx = relIndex;

      addRequiredTagColumn(pCmd, pCmd->groupbyExpr.columnInfo[0].colIdx, 0);
    }
  }
}