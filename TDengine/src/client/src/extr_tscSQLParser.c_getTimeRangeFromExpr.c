#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ nSQLOptr; struct TYPE_16__* pRight; int /*<<< orphan*/  colInfo; struct TYPE_16__* pLeft; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  scalar_t__ int32_t ;
struct TYPE_20__ {int /*<<< orphan*/  tableIndex; } ;
struct TYPE_19__ {int /*<<< orphan*/  precision; } ;
struct TYPE_18__ {TYPE_4__* pMeterMeta; } ;
struct TYPE_17__ {scalar_t__ stime; scalar_t__ etime; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_2__ SSqlCmd ;
typedef  TYPE_3__ SMeterMetaInfo ;
typedef  TYPE_4__ SMeterMeta ;
typedef  TYPE_5__ SColumnIndex ;

/* Variables and functions */
 TYPE_5__ COLUMN_INDEX_INITIALIZER ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ TK_OR ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ getColumnIndexByNameEx (int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*) ; 
 scalar_t__ getTimeRange (scalar_t__*,scalar_t__*,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isExprDirectParentOfLeaftNode (TYPE_1__*) ; 
 int /*<<< orphan*/  setErrMsg (TYPE_2__*,char const*) ; 
 TYPE_3__* tscGetMeterMetaInfo (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t getTimeRangeFromExpr(SSqlCmd* pCmd, tSQLExpr* pExpr) {
  const char* msg0 = "invalid timestamp";
  const char* msg1 = "only one time stamp window allowed";

  if (pExpr == NULL) {
    return TSDB_CODE_SUCCESS;
  }

  if (!isExprDirectParentOfLeaftNode(pExpr)) {
    if (pExpr->nSQLOptr == TK_OR) {
      setErrMsg(pCmd, msg1);
      return TSDB_CODE_INVALID_SQL;
    }

    getTimeRangeFromExpr(pCmd, pExpr->pLeft);

    return getTimeRangeFromExpr(pCmd, pExpr->pRight);
  } else {
    SColumnIndex index = COLUMN_INDEX_INITIALIZER;
    if (getColumnIndexByNameEx(&pExpr->pLeft->colInfo, pCmd, &index) != TSDB_CODE_SUCCESS) {
      return TSDB_CODE_INVALID_SQL;
    }

    SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, index.tableIndex);
    SMeterMeta*     pMeterMeta = pMeterMetaInfo->pMeterMeta;

    tSQLExpr* pRight = pExpr->pRight;

    TSKEY stime = 0;
    TSKEY etime = INT64_MAX;

    if (getTimeRange(&stime, &etime, pRight, pExpr->nSQLOptr, pMeterMeta->precision) != TSDB_CODE_SUCCESS) {
      setErrMsg(pCmd, msg0);
      return TSDB_CODE_INVALID_SQL;
    }

    // update the timestamp query range
    if (pCmd->stime < stime) {
      pCmd->stime = stime;
    }

    if (pCmd->etime > etime) {
      pCmd->etime = etime;
    }
  }

  return TSDB_CODE_SUCCESS;
}