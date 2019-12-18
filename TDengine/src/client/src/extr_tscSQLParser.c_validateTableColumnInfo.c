#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nField; TYPE_2__* p; } ;
typedef  TYPE_1__ tFieldList ;
typedef  size_t int32_t ;
struct TYPE_6__ {scalar_t__ type; size_t bytes; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ TAOS_FIELD ;
typedef  int /*<<< orphan*/  SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 scalar_t__ TSDB_DATA_TYPE_BOOL ; 
 scalar_t__ TSDB_DATA_TYPE_NCHAR ; 
 scalar_t__ TSDB_DATA_TYPE_TIMESTAMP ; 
 scalar_t__ TSDB_MAX_BINARY_LEN ; 
 size_t TSDB_MAX_BYTES_PER_ROW ; 
 int TSDB_MAX_COLUMNS ; 
 scalar_t__ TSDB_MAX_NCHAR_LEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int has (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setErrMsg (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ validateColumnName (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool validateTableColumnInfo(tFieldList* pFieldList, SSqlCmd* pCmd) {
  assert(pFieldList != NULL);

  const char* msg = "illegal number of columns";
  const char* msg1 = "first column must be timestamp";
  const char* msg2 = "row length exceeds max length";
  const char* msg3 = "duplicated column names";
  const char* msg4 = "invalid data types";
  const char* msg5 = "invalid binary/nchar column length";
  const char* msg6 = "invalid column name";

  // number of fields no less than 2
  if (pFieldList->nField <= 1 || pFieldList->nField > TSDB_MAX_COLUMNS) {
    setErrMsg(pCmd, msg);
    return false;
  }

  // first column must be timestamp
  if (pFieldList->p[0].type != TSDB_DATA_TYPE_TIMESTAMP) {
    setErrMsg(pCmd, msg1);
    return false;
  }

  int32_t nLen = 0;
  for (int32_t i = 0; i < pFieldList->nField; ++i) {
    nLen += pFieldList->p[i].bytes;
  }

  // max row length must be less than TSDB_MAX_BYTES_PER_ROW
  if (nLen > TSDB_MAX_BYTES_PER_ROW) {
    setErrMsg(pCmd, msg2);
    return false;
  }

  // field name must be unique
  for (int32_t i = 0; i < pFieldList->nField; ++i) {
    TAOS_FIELD* pField = &pFieldList->p[i];
    if (pField->type < TSDB_DATA_TYPE_BOOL || pField->type > TSDB_DATA_TYPE_NCHAR) {
      setErrMsg(pCmd, msg4);
      return false;
    }

    if ((pField->type == TSDB_DATA_TYPE_BINARY && (pField->bytes <= 0 || pField->bytes > TSDB_MAX_BINARY_LEN)) ||
        (pField->type == TSDB_DATA_TYPE_NCHAR && (pField->bytes <= 0 || pField->bytes > TSDB_MAX_NCHAR_LEN))) {
      setErrMsg(pCmd, msg5);
      return false;
    }

    if (validateColumnName(pField->name) != TSDB_CODE_SUCCESS) {
      setErrMsg(pCmd, msg6);
      return false;
    }

    if (has(pFieldList, i + 1, pFieldList->p[i].name) == true) {
      setErrMsg(pCmd, msg3);
      return false;
    }
  }

  return true;
}