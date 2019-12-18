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
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  dKey; } ;
struct TYPE_11__ {scalar_t__ n; int /*<<< orphan*/  z; } ;
struct TYPE_14__ {scalar_t__ nSQLOptr; TYPE_3__ val; TYPE_1__ colInfo; } ;
typedef  TYPE_4__ tSQLExpr ;
typedef  size_t int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_16__ {int /*<<< orphan*/  num; TYPE_2__* ids; } ;
struct TYPE_17__ {TYPE_6__ list; } ;
struct TYPE_15__ {scalar_t__ type; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {scalar_t__ columnIndex; } ;
typedef  TYPE_5__ SSchema ;
typedef  TYPE_6__ SColumnList ;
typedef  TYPE_7__ SColumnIdListRes ;

/* Variables and functions */
 scalar_t__ TK_FLOAT ; 
 scalar_t__ TK_ID ; 
 scalar_t__ TK_LAST_ROW ; 
 scalar_t__ TK_MIN ; 
 size_t TSDB_CODE_INVALID_SQL ; 
 size_t TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_DATA_TYPE_DOUBLE ; 
 scalar_t__ TSDB_DATA_TYPE_TINYINT ; 
 scalar_t__ isinf (int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int32_t validateSQLExpr(tSQLExpr* pExpr, SSchema* pSchema, int32_t numOfCols, SColumnIdListRes* pList) {
  if (pExpr->nSQLOptr == TK_ID) {
    bool validColumnName = false;

    SColumnList* list = &pList->list;

    for (int32_t i = 0; i < numOfCols; ++i) {
      if (strncasecmp(pExpr->colInfo.z, pSchema[i].name, pExpr->colInfo.n) == 0 &&
          pExpr->colInfo.n == strlen(pSchema[i].name)) {
        if (pSchema[i].type < TSDB_DATA_TYPE_TINYINT || pSchema[i].type > TSDB_DATA_TYPE_DOUBLE) {
          return TSDB_CODE_INVALID_SQL;
        }

        if (pList != NULL) {
          list->ids[list->num++].columnIndex = (int16_t)i;
        }

        validColumnName = true;
      }
    }

    if (!validColumnName) {
      return TSDB_CODE_INVALID_SQL;
    }

  } else if (pExpr->nSQLOptr == TK_FLOAT && (isnan(pExpr->val.dKey) || isinf(pExpr->val.dKey))) {
    return TSDB_CODE_INVALID_SQL;
  } else if (pExpr->nSQLOptr >= TK_MIN && pExpr->nSQLOptr <= TK_LAST_ROW) {
    return TSDB_CODE_INVALID_SQL;
  }

  return TSDB_CODE_SUCCESS;
}