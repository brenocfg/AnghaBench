#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ nType; int nLen; int /*<<< orphan*/  pz; } ;
struct TYPE_16__ {TYPE_10__ pVar; } ;
typedef  TYPE_2__ tVariantListItem ;
struct TYPE_17__ {int nExpr; TYPE_2__* a; } ;
typedef  TYPE_3__ tVariantList ;
typedef  size_t int32_t ;
struct TYPE_20__ {TYPE_3__* fillType; } ;
struct TYPE_15__ {size_t numOfOutputCols; } ;
struct TYPE_19__ {int /*<<< orphan*/ * defaultVal; TYPE_1__ fieldsInfo; int /*<<< orphan*/  interpoType; } ;
struct TYPE_18__ {scalar_t__ type; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_4__ TAOS_FIELD ;
typedef  TYPE_5__ SSqlCmd ;
typedef  TYPE_6__ SQuerySQL ;

/* Variables and functions */
 size_t TSDB_CODE_INVALID_SQL ; 
 size_t TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 scalar_t__ TSDB_DATA_TYPE_NCHAR ; 
 int /*<<< orphan*/  TSDB_INTERPO_LINEAR ; 
 int /*<<< orphan*/  TSDB_INTERPO_NONE ; 
 int /*<<< orphan*/  TSDB_INTERPO_NULL ; 
 int /*<<< orphan*/  TSDB_INTERPO_PREV ; 
 int /*<<< orphan*/  TSDB_INTERPO_SET_VALUE ; 
 int /*<<< orphan*/  setErrMsg (TYPE_5__*,char const*) ; 
 int /*<<< orphan*/  setNull (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,char*,int) ; 
 size_t tVariantDump (TYPE_10__*,char*,scalar_t__) ; 
 TYPE_4__* tscFieldInfoGetField (TYPE_5__*,size_t) ; 
 scalar_t__ tscIsPointInterpQuery (TYPE_5__*) ; 

int32_t parseFillClause(SSqlCmd* pCmd, SQuerySQL* pQuerySQL) {
  tVariantList*     pFillToken = pQuerySQL->fillType;
  tVariantListItem* pItem = &pFillToken->a[0];

  const int32_t START_INTERPO_COL_IDX = 1;
  const char*   msg = "illegal value or data overflow";
  const char*   msg1 = "value is expected";
  const char*   msg2 = "invalid fill option";

  if (pItem->pVar.nType != TSDB_DATA_TYPE_BINARY) {
    setErrMsg(pCmd, msg2);
    return TSDB_CODE_INVALID_SQL;
  }

  if (strncasecmp(pItem->pVar.pz, "none", 4) == 0 && pItem->pVar.nLen == 4) {
    pCmd->interpoType = TSDB_INTERPO_NONE;
  } else if (strncasecmp(pItem->pVar.pz, "null", 4) == 0 && pItem->pVar.nLen == 4) {
    pCmd->interpoType = TSDB_INTERPO_NULL;
    for (int32_t i = START_INTERPO_COL_IDX; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
      TAOS_FIELD* pFields = tscFieldInfoGetField(pCmd, i);
      setNull((char*)&pCmd->defaultVal[i], pFields->type, pFields->bytes);
    }
  } else if (strncasecmp(pItem->pVar.pz, "prev", 4) == 0 && pItem->pVar.nLen == 4) {
    pCmd->interpoType = TSDB_INTERPO_PREV;
  } else if (strncasecmp(pItem->pVar.pz, "linear", 6) == 0 && pItem->pVar.nLen == 6) {
    //         not support yet
    pCmd->interpoType = TSDB_INTERPO_LINEAR;
  } else if (strncasecmp(pItem->pVar.pz, "value", 5) == 0 && pItem->pVar.nLen == 5) {
    pCmd->interpoType = TSDB_INTERPO_SET_VALUE;

    if (pFillToken->nExpr == 1) {
      setErrMsg(pCmd, msg1);
      return TSDB_CODE_INVALID_SQL;
    }

    int32_t startPos = 1;
    int32_t numOfFillVal = pFillToken->nExpr - 1;

    /* for point interpolation query, we do not have the timestamp column */
    if (tscIsPointInterpQuery(pCmd)) {
      startPos = 0;

      if (numOfFillVal > pCmd->fieldsInfo.numOfOutputCols) {
        numOfFillVal = pCmd->fieldsInfo.numOfOutputCols;
      }
    } else {
      numOfFillVal =
          (pFillToken->nExpr > pCmd->fieldsInfo.numOfOutputCols) ? pCmd->fieldsInfo.numOfOutputCols : pFillToken->nExpr;
    }

    int32_t j = 1;

    for (int32_t i = startPos; i < numOfFillVal; ++i, ++j) {
      TAOS_FIELD* pFields = tscFieldInfoGetField(pCmd, i);

      int32_t ret = tVariantDump(&pFillToken->a[j].pVar, (char*)&pCmd->defaultVal[i], pFields->type);
      if (ret != TSDB_CODE_SUCCESS) {
        setErrMsg(pCmd, msg);
        return TSDB_CODE_INVALID_SQL;
      }

      if (pFields->type == TSDB_DATA_TYPE_BINARY || pFields->type == TSDB_DATA_TYPE_NCHAR) {
        setNull((char*)(&pCmd->defaultVal[i]), pFields->type, pFields->bytes);
      }
    }

    if ((pFillToken->nExpr < pCmd->fieldsInfo.numOfOutputCols) ||
        ((pFillToken->nExpr - 1 < pCmd->fieldsInfo.numOfOutputCols) && (tscIsPointInterpQuery(pCmd)))) {
      tVariantListItem* lastItem = &pFillToken->a[pFillToken->nExpr - 1];

      for (int32_t i = numOfFillVal; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
        TAOS_FIELD* pFields = tscFieldInfoGetField(pCmd, i);
        tVariantDump(&lastItem->pVar, (char*)&pCmd->defaultVal[i], pFields->type);

        if (pFields->type == TSDB_DATA_TYPE_BINARY || pFields->type == TSDB_DATA_TYPE_NCHAR) {
          setNull((char*)(&pCmd->defaultVal[i]), pFields->type, pFields->bytes);
        }
      }
    }
  } else {
    setErrMsg(pCmd, msg2);
    return TSDB_CODE_INVALID_SQL;
  }

  return TSDB_CODE_SUCCESS;
}