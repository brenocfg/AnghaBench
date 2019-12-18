#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_17__ {TYPE_3__* pMeterMeta; } ;
struct TYPE_16__ {scalar_t__ member_0; scalar_t__ member_1; } ;
struct TYPE_15__ {scalar_t__ numOfColumns; } ;
struct TYPE_14__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  SSqlExpr ;
typedef  TYPE_1__ SSqlCmd ;
typedef  TYPE_2__ SSchema ;
typedef  TYPE_3__ SMeterMeta ;
typedef  TYPE_4__ SColumnIndex ;

/* Variables and functions */
 scalar_t__ TSDB_FUNC_PRJ ; 
 scalar_t__ TSDB_FUNC_TAGPRJ ; 
 int /*<<< orphan*/  TSDB_QUERY_TYPE_PROJECTION_QUERY ; 
 int /*<<< orphan*/  TSDB_QUERY_TYPE_STABLE_QUERY ; 
 int /*<<< orphan*/  addRequiredTagColumn (TYPE_1__*,scalar_t__,scalar_t__) ; 
 TYPE_2__* tsGetColumnSchema (TYPE_3__*,scalar_t__) ; 
 TYPE_7__* tscGetMeterMetaInfo (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * tscSqlExprInsert (TYPE_1__*,scalar_t__,scalar_t__,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SSqlExpr* doAddProjectCol(SSqlCmd* pCmd, int32_t outputIndex, int32_t colIdx, int32_t tableIndex) {
  SMeterMeta* pMeterMeta = tscGetMeterMetaInfo(pCmd, tableIndex)->pMeterMeta;

  SSchema* pSchema = tsGetColumnSchema(pMeterMeta, colIdx);
  int32_t  numOfCols = pMeterMeta->numOfColumns;

  int16_t functionId = (int16_t)((colIdx >= numOfCols) ? TSDB_FUNC_TAGPRJ : TSDB_FUNC_PRJ);

  if (functionId == TSDB_FUNC_TAGPRJ) {
    addRequiredTagColumn(pCmd, colIdx - numOfCols, tableIndex);
    pCmd->type = TSDB_QUERY_TYPE_STABLE_QUERY;
  } else {
    pCmd->type = TSDB_QUERY_TYPE_PROJECTION_QUERY;
  }

  SColumnIndex index = {tableIndex, colIdx};
  SSqlExpr*    pExpr =
      tscSqlExprInsert(pCmd, outputIndex, functionId, &index, pSchema->type, pSchema->bytes, pSchema->bytes);

  return pExpr;
}