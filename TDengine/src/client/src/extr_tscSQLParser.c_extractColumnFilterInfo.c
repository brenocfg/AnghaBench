#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ nSQLOptr; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  scalar_t__ int32_t ;
struct TYPE_21__ {int /*<<< orphan*/  columnIndex; int /*<<< orphan*/  tableIndex; } ;
struct TYPE_23__ {scalar_t__ numOfFilters; TYPE_4__ colIndex; TYPE_5__* filterInfo; } ;
struct TYPE_22__ {int filterOnBinary; } ;
struct TYPE_20__ {int /*<<< orphan*/ * pMeterMeta; } ;
struct TYPE_19__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_2__ SSchema ;
typedef  TYPE_3__ SMeterMetaInfo ;
typedef  int /*<<< orphan*/  SMeterMeta ;
typedef  TYPE_4__ SColumnIndex ;
typedef  TYPE_5__ SColumnFilterInfo ;
typedef  TYPE_6__ SColumnBase ;

/* Variables and functions */
 scalar_t__ TK_AND ; 
 scalar_t__ TK_EQ ; 
 scalar_t__ TK_LIKE ; 
 scalar_t__ TK_NE ; 
 scalar_t__ TK_OR ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 scalar_t__ TSDB_DATA_TYPE_NCHAR ; 
 TYPE_5__* addColumnFilterInfo (TYPE_6__*) ; 
 scalar_t__ doExtractColumnFilterInfo (int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  setErrMsg (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* tsGetColumnSchema (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* tscColumnBaseInfoInsert (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_3__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t extractColumnFilterInfo(SSqlCmd* pCmd, SColumnIndex* pIndex, tSQLExpr* pExpr, int32_t sqlOptr) {
  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, pIndex->tableIndex);

  SMeterMeta* pMeterMeta = pMeterMetaInfo->pMeterMeta;
  SSchema*    pSchema = tsGetColumnSchema(pMeterMeta, pIndex->columnIndex);

  const char* msg1 = "non binary column not support like operator";
  const char* msg2 = "binary column not support this operator";
  const char* msg3 = "OR is not supported on different column filter";

  SColumnBase*       pColumn = tscColumnBaseInfoInsert(pCmd, pIndex);
  SColumnFilterInfo* pColFilter = NULL;

  /*
   * in case of TK_AND filter condition, we first find the corresponding column and build the query condition together
   * the already existed condition.
   */
  if (sqlOptr == TK_AND) {
    // this is a new filter condition on this column
    if (pColumn->numOfFilters == 0) {
      pColFilter = addColumnFilterInfo(pColumn);
    } else {  // update the existed column filter information, find the filter info here
      pColFilter = &pColumn->filterInfo[0];
    }
  } else if (sqlOptr == TK_OR) {
    // TODO fixme: failed to invalid the filter expression: "col1 = 1 OR col2 = 2"
    pColFilter = addColumnFilterInfo(pColumn);
  } else {  // error;
    return TSDB_CODE_INVALID_SQL;
  }

  pColFilter->filterOnBinary =
      ((pSchema->type == TSDB_DATA_TYPE_BINARY || pSchema->type == TSDB_DATA_TYPE_NCHAR) ? 1 : 0);

  if (pColFilter->filterOnBinary) {
    if (pExpr->nSQLOptr != TK_EQ && pExpr->nSQLOptr != TK_NE && pExpr->nSQLOptr != TK_LIKE) {
      setErrMsg(pCmd, msg2);
      return TSDB_CODE_INVALID_SQL;
    }
  } else {
    if (pExpr->nSQLOptr == TK_LIKE) {
      setErrMsg(pCmd, msg1);
      return TSDB_CODE_INVALID_SQL;
    }
  }

  pColumn->colIndex = *pIndex;
  return doExtractColumnFilterInfo(pCmd, pColFilter, pIndex, pExpr);
}