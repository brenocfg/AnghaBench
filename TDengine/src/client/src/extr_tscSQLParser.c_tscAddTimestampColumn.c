#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int16_t ;
struct TYPE_17__ {scalar_t__ member_0; scalar_t__ member_1; } ;
struct TYPE_14__ {scalar_t__ numOfExprs; } ;
struct TYPE_16__ {TYPE_2__ exprsInfo; } ;
struct TYPE_13__ {scalar_t__ colId; int /*<<< orphan*/  flag; } ;
struct TYPE_15__ {scalar_t__ functionId; TYPE_1__ colInfo; } ;
typedef  TYPE_3__ SSqlExpr ;
typedef  TYPE_4__ SSqlCmd ;
typedef  int /*<<< orphan*/  SColumnList ;
typedef  TYPE_5__ SColumnIndex ;

/* Variables and functions */
 scalar_t__ PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 int /*<<< orphan*/  TSDB_COL_NORMAL ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_TIMESTAMP ; 
 int /*<<< orphan*/  TSDB_KEYSIZE ; 
 int /*<<< orphan*/  getColumnList (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  insertResultField (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* tscSqlExprGet (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tscSqlExprInsert (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tscAddTimestampColumn(SSqlCmd* pCmd, int16_t functionId, int16_t tableIndex) {
  // the first column not timestamp column, add it
  SSqlExpr* pExpr = NULL;
  if (pCmd->exprsInfo.numOfExprs > 0) {
    pExpr = tscSqlExprGet(pCmd, 0);
  }

  if (pExpr == NULL || pExpr->colInfo.colId != PRIMARYKEY_TIMESTAMP_COL_INDEX || pExpr->functionId != functionId) {
    SColumnIndex index = {tableIndex, PRIMARYKEY_TIMESTAMP_COL_INDEX};

    pExpr = tscSqlExprInsert(pCmd, 0, functionId, &index, TSDB_DATA_TYPE_TIMESTAMP, TSDB_KEYSIZE, TSDB_KEYSIZE);
    pExpr->colInfo.flag = TSDB_COL_NORMAL;

    // NOTE: tag column does not add to source column list
    SColumnList ids = getColumnList(1, tableIndex, PRIMARYKEY_TIMESTAMP_COL_INDEX);

    insertResultField(pCmd, 0, &ids, TSDB_KEYSIZE, TSDB_DATA_TYPE_TIMESTAMP, "ts");
  }
}