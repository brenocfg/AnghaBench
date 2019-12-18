#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_14__ {scalar_t__ columnIndex; scalar_t__ tableIndex; } ;
struct TYPE_13__ {int /*<<< orphan*/  n; int /*<<< orphan*/  z; } ;
struct TYPE_12__ {scalar_t__ numOfTables; } ;
typedef  TYPE_1__ SSqlCmd ;
typedef  TYPE_2__ SSQLToken ;
typedef  TYPE_3__ SColumnIndex ;

/* Variables and functions */
 scalar_t__ COLUMN_INDEX_INITIAL_VAL ; 
 scalar_t__ COLUMN_INDEX_VALIDE (TYPE_3__) ; 
 int /*<<< orphan*/  DEFAULT_PRIMARY_TIMESTAMP_COL_NAME ; 
 scalar_t__ PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 int /*<<< orphan*/  TSDB_CODE_INVALID_SQL ; 
 int /*<<< orphan*/  TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_TBNAME_COLUMN_INDEX ; 
 scalar_t__ doGetColumnIndex (TYPE_1__*,scalar_t__,TYPE_2__*) ; 
 scalar_t__ isTablenameToken (TYPE_2__*) ; 
 int /*<<< orphan*/  setErrMsg (TYPE_1__*,char const*) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t doGetColumnIndexByName(SSQLToken* pToken, SSqlCmd* pCmd, SColumnIndex* pIndex) {
  const char* msg0 = "ambiguous column name";
  const char* msg1 = "invalid column name";

  if (isTablenameToken(pToken)) {
    pIndex->columnIndex = TSDB_TBNAME_COLUMN_INDEX;
  } else if (strncasecmp(pToken->z, DEFAULT_PRIMARY_TIMESTAMP_COL_NAME, pToken->n) == 0) {
    pIndex->columnIndex = PRIMARYKEY_TIMESTAMP_COL_INDEX;
  } else {
    // not specify the table name, try to locate the table index by column name
    if (pIndex->tableIndex == COLUMN_INDEX_INITIAL_VAL) {
      for (int16_t i = 0; i < pCmd->numOfTables; ++i) {
        int16_t colIndex = doGetColumnIndex(pCmd, i, pToken);

        if (colIndex != COLUMN_INDEX_INITIAL_VAL) {
          if (pIndex->columnIndex != COLUMN_INDEX_INITIAL_VAL) {
            setErrMsg(pCmd, msg0);
            return TSDB_CODE_INVALID_SQL;
          } else {
            pIndex->tableIndex = i;
            pIndex->columnIndex = colIndex;
          }
        }
      }
    } else {  // table index is valid, get the column index
      int16_t colIndex = doGetColumnIndex(pCmd, pIndex->tableIndex, pToken);
      if (colIndex != COLUMN_INDEX_INITIAL_VAL) {
        pIndex->columnIndex = colIndex;
      }
    }

    if (pIndex->columnIndex == COLUMN_INDEX_INITIAL_VAL) {
      setErrMsg(pCmd, msg1);
      return TSDB_CODE_INVALID_SQL;
    }
  }

  if (COLUMN_INDEX_VALIDE(*pIndex)) {
    return TSDB_CODE_SUCCESS;
  } else {
    return TSDB_CODE_INVALID_SQL;
  }
}