#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nType; scalar_t__ nLen; int i64Key; int dKey; int /*<<< orphan*/  pz; } ;
struct TYPE_5__ {scalar_t__ nSQLOptr; TYPE_3__ val; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  int int64_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_6__ {scalar_t__ n; scalar_t__ type; int /*<<< orphan*/  z; } ;
typedef  TYPE_2__ SSQLToken ;

/* Variables and functions */
 int INT64_MAX ; 
 scalar_t__ TK_EQ ; 
 scalar_t__ TK_FLOAT ; 
 scalar_t__ TK_GE ; 
 scalar_t__ TK_GT ; 
 scalar_t__ TK_ID ; 
 scalar_t__ TK_IN ; 
 scalar_t__ TK_INTEGER ; 
 scalar_t__ TK_LE ; 
 scalar_t__ TK_LT ; 
 scalar_t__ TK_SET ; 
 scalar_t__ TK_STRING ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_BIGINT ; 
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 int /*<<< orphan*/  TSDB_TIME_PRECISION_MICRO ; 
 scalar_t__ TSDB_TIME_PRECISION_MILLI ; 
 scalar_t__ strdequote (int /*<<< orphan*/ ) ; 
 char* strnchr (int /*<<< orphan*/ ,char,scalar_t__,int) ; 
 scalar_t__ tSQLGetToken (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  tVariantDump (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ taosParseTime (int /*<<< orphan*/ ,int*,scalar_t__,int /*<<< orphan*/ ) ; 

int32_t getTimeRange(int64_t* stime, int64_t* etime, tSQLExpr* pRight, int32_t optr, int16_t timePrecision) {
  // this is join condition, do nothing
  if (pRight->nSQLOptr == TK_ID) {
    return TSDB_CODE_SUCCESS;
  }

  /*
   * filter primary ts filter expression like:
   * where ts in ('2015-12-12 4:8:12')
   */
  if (pRight->nSQLOptr == TK_SET || optr == TK_IN) {
    return TSDB_CODE_INVALID_SQL;
  }

  int64_t val = 0;
  bool    parsed = false;
  if (pRight->val.nType == TSDB_DATA_TYPE_BINARY) {
    pRight->val.nLen = strdequote(pRight->val.pz);

    char* seg = strnchr(pRight->val.pz, '-', pRight->val.nLen, false);
    if (seg != NULL) {
      if (taosParseTime(pRight->val.pz, &val, pRight->val.nLen, TSDB_TIME_PRECISION_MICRO) == TSDB_CODE_SUCCESS) {
        parsed = true;
      } else {
        return TSDB_CODE_INVALID_SQL;
      }
    } else {
      SSQLToken token = {.z = pRight->val.pz, .n = pRight->val.nLen, .type = TK_ID};
      int32_t   len = tSQLGetToken(pRight->val.pz, &token.type);

      if ((token.type != TK_INTEGER && token.type != TK_FLOAT) || len != pRight->val.nLen) {
        return TSDB_CODE_INVALID_SQL;
      }
    }
  } else if (pRight->nSQLOptr == TK_INTEGER && timePrecision == TSDB_TIME_PRECISION_MILLI) {
    /*
     * if the pRight->nSQLOptr == TK_INTEGER/TK_FLOAT, the value is adaptive, we
     * need the time precision in metermeta to transfer the value in MICROSECOND
     *
     * Additional check to avoid data overflow
     */
    if (pRight->val.i64Key <= INT64_MAX / 1000) {
      pRight->val.i64Key *= 1000;
    }
  } else if (pRight->nSQLOptr == TK_FLOAT && timePrecision == TSDB_TIME_PRECISION_MILLI) {
    pRight->val.dKey *= 1000;
  }

  if (!parsed) {
    /*
     * failed to parse timestamp in regular formation, try next
     * it may be a epoch time in string format
     */
    tVariantDump(&pRight->val, (char*)&val, TSDB_DATA_TYPE_BIGINT);

    /*
     * transfer it into MICROSECOND format if it is a string, since for
     * TK_INTEGER/TK_FLOAT the value has been transferred
     *
     * additional check to avoid data overflow
     */
    if (pRight->nSQLOptr == TK_STRING && timePrecision == TSDB_TIME_PRECISION_MILLI) {
      if (val <= INT64_MAX / 1000) {
        val *= 1000;
      }
    }
  }

  int32_t delta = 1;
  /* for millisecond, delta is 1ms=1000us */
  if (timePrecision == TSDB_TIME_PRECISION_MILLI) {
    delta *= 1000;
  }

  if (optr == TK_LE) {
    *etime = val;
  } else if (optr == TK_LT) {
    *etime = val - delta;
  } else if (optr == TK_GT) {
    *stime = val + delta;
  } else if (optr == TK_GE) {
    *stime = val;
  } else if (optr == TK_EQ) {
    *stime = val;
    *etime = *stime;
  }
  return TSDB_CODE_SUCCESS;
}