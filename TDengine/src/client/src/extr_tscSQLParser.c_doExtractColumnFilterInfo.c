#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_18__ {scalar_t__ nType; int nLen; } ;
struct TYPE_13__ {int nSQLOptr; TYPE_8__ val; struct TYPE_13__* pRight; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  void* int64_t ;
typedef  int int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_17__ {size_t len; int /*<<< orphan*/  lowerRelOptr; int /*<<< orphan*/  upperRelOptr; int /*<<< orphan*/  lowerBndd; void* pz; int /*<<< orphan*/  upperBndd; } ;
struct TYPE_16__ {int /*<<< orphan*/  columnIndex; int /*<<< orphan*/  tableIndex; } ;
struct TYPE_15__ {int /*<<< orphan*/  pMeterMeta; } ;
struct TYPE_14__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_2__ SSchema ;
typedef  TYPE_3__ SMeterMetaInfo ;
typedef  TYPE_4__ SColumnIndex ;
typedef  TYPE_5__ SColumnFilterInfo ;

/* Variables and functions */
#define  TK_EQ 134 
#define  TK_GE 133 
#define  TK_GT 132 
#define  TK_LE 131 
#define  TK_LIKE 130 
#define  TK_LT 129 
#define  TK_NE 128 
 int TSDB_CODE_INVALID_SQL ; 
 int TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_DATA_TYPE_BIGINT ; 
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 scalar_t__ TSDB_DATA_TYPE_DOUBLE ; 
 scalar_t__ TSDB_DATA_TYPE_FLOAT ; 
 scalar_t__ TSDB_DATA_TYPE_NCHAR ; 
 scalar_t__ TSDB_DATA_TYPE_TIMESTAMP ; 
 scalar_t__ TSDB_DATA_TYPE_TINYINT ; 
 int TSDB_NCHAR_SIZE ; 
 int /*<<< orphan*/  TSDB_RELATION_EQUAL ; 
 int /*<<< orphan*/  TSDB_RELATION_LARGE ; 
 int /*<<< orphan*/  TSDB_RELATION_LARGE_EQUAL ; 
 int /*<<< orphan*/  TSDB_RELATION_LESS ; 
 int /*<<< orphan*/  TSDB_RELATION_LESS_EQUAL ; 
 int /*<<< orphan*/  TSDB_RELATION_LIKE ; 
 int /*<<< orphan*/  TSDB_RELATION_NOT_EQUAL ; 
 scalar_t__ calloc (int,int) ; 
 int setColumnFilterInfoForTimestamp (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  setErrMsg (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  tVariantDump (TYPE_8__*,char*,scalar_t__) ; 
 TYPE_2__* tsGetColumnSchema (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t doExtractColumnFilterInfo(SSqlCmd* pCmd, SColumnFilterInfo* pColumnFilter, SColumnIndex* columnIndex,
                                         tSQLExpr* pExpr) {
  const char* msg = "not supported filter condition";

  tSQLExpr*       pRight = pExpr->pRight;
  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, columnIndex->tableIndex);

  SSchema* pSchema = tsGetColumnSchema(pMeterMetaInfo->pMeterMeta, columnIndex->columnIndex);

  int16_t colType = pSchema->type;
  if (colType >= TSDB_DATA_TYPE_TINYINT && colType <= TSDB_DATA_TYPE_BIGINT) {
    colType = TSDB_DATA_TYPE_BIGINT;
  } else if (colType == TSDB_DATA_TYPE_FLOAT || colType == TSDB_DATA_TYPE_DOUBLE) {
    colType = TSDB_DATA_TYPE_DOUBLE;
  } else if ((colType == TSDB_DATA_TYPE_TIMESTAMP) && (TSDB_DATA_TYPE_BINARY == pRight->val.nType)) {
    int retVal = setColumnFilterInfoForTimestamp(pCmd, &pRight->val);
    if (TSDB_CODE_SUCCESS != retVal) {
      return retVal;
    }
  }

  if (pExpr->nSQLOptr == TK_LE || pExpr->nSQLOptr == TK_LT) {
    tVariantDump(&pRight->val, (char*)&pColumnFilter->upperBndd, colType);
  } else {  // TK_GT,TK_GE,TK_EQ,TK_NE are based on the pColumn->lowerBndd
    if (colType == TSDB_DATA_TYPE_BINARY) {
      pColumnFilter->pz = (int64_t)calloc(1, pRight->val.nLen + 1);
      pColumnFilter->len = pRight->val.nLen;

      tVariantDump(&pRight->val, (char*)pColumnFilter->pz, colType);
    } else if (colType == TSDB_DATA_TYPE_NCHAR) {
      // pRight->val.nLen + 1 is larger than the actual nchar string length
      pColumnFilter->pz = (int64_t)calloc(1, (pRight->val.nLen + 1) * TSDB_NCHAR_SIZE);

      tVariantDump(&pRight->val, (char*)pColumnFilter->pz, colType);

      size_t len = wcslen((wchar_t*)pColumnFilter->pz);
      pColumnFilter->len = len * TSDB_NCHAR_SIZE;
    } else {
      tVariantDump(&pRight->val, (char*)&pColumnFilter->lowerBndd, colType);
    }
  }

  switch (pExpr->nSQLOptr) {
    case TK_LE:
      pColumnFilter->upperRelOptr = TSDB_RELATION_LESS_EQUAL;
      break;
    case TK_LT:
      pColumnFilter->upperRelOptr = TSDB_RELATION_LESS;
      break;
    case TK_GT:
      pColumnFilter->lowerRelOptr = TSDB_RELATION_LARGE;
      break;
    case TK_GE:
      pColumnFilter->lowerRelOptr = TSDB_RELATION_LARGE_EQUAL;
      break;
    case TK_EQ:
      pColumnFilter->lowerRelOptr = TSDB_RELATION_EQUAL;
      break;
    case TK_NE:
      pColumnFilter->lowerRelOptr = TSDB_RELATION_NOT_EQUAL;
      break;
    case TK_LIKE:
      pColumnFilter->lowerRelOptr = TSDB_RELATION_LIKE;
      break;
    default:
      setErrMsg(pCmd, msg);
      return TSDB_CODE_INVALID_SQL;
  }

  return TSDB_CODE_SUCCESS;
}