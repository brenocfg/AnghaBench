#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_12__ {scalar_t__ numOfColumns; scalar_t__ numOfTags; } ;
struct TYPE_11__ {TYPE_4__* pMeterMeta; } ;
struct TYPE_10__ {size_t bytes; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {scalar_t__ type; scalar_t__ bytes; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ TAOS_FIELD ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_2__ SSchema ;
typedef  TYPE_3__ SMeterMetaInfo ;
typedef  TYPE_4__ SMeterMeta ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_COL_NAME_LEN ; 
 scalar_t__ TSDB_DATA_TYPE_BOOL ; 
 scalar_t__ TSDB_DATA_TYPE_NCHAR ; 
 size_t TSDB_MAX_BYTES_PER_ROW ; 
 scalar_t__ TSDB_MAX_COLUMNS ; 
 int /*<<< orphan*/  setErrMsg (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* tsGetSchema (TYPE_4__*) ; 
 TYPE_3__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ validateColumnName (int /*<<< orphan*/ ) ; 

bool validateOneColumn(SSqlCmd* pCmd, TAOS_FIELD* pColField) {
  const char* msg1 = "too many columns";
  const char* msg2 = "duplicated column names";
  const char* msg3 = "column length too long";
  const char* msg4 = "invalid data types";
  const char* msg5 = "invalid column name";
  const char* msg6 = "invalid column length";

  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);
  SMeterMeta*     pMeterMeta = pMeterMetaInfo->pMeterMeta;

  // no more max columns
  if (pMeterMeta->numOfColumns >= TSDB_MAX_COLUMNS ||
      pMeterMeta->numOfTags + pMeterMeta->numOfColumns >= TSDB_MAX_COLUMNS) {
    setErrMsg(pCmd, msg1);
    return false;
  }

  if (pColField->type < TSDB_DATA_TYPE_BOOL || pColField->type > TSDB_DATA_TYPE_NCHAR) {
    setErrMsg(pCmd, msg4);
    return false;
  }

  if (validateColumnName(pColField->name) != TSDB_CODE_SUCCESS) {
    setErrMsg(pCmd, msg5);
    return false;
  }

  SSchema* pSchema = tsGetSchema(pMeterMeta);
  int32_t  nLen = 0;

  for (int32_t i = 0; i < pMeterMeta->numOfColumns; ++i) {
    nLen += pSchema[i].bytes;
  }

  if (pColField->bytes <= 0) {
    setErrMsg(pCmd, msg6);
    return false;
  }

  // length less than TSDB_MAX_BYTES_PER_ROW
  if (nLen + pColField->bytes > TSDB_MAX_BYTES_PER_ROW) {
    setErrMsg(pCmd, msg3);
    return false;
  }

  // field name must be unique
  for (int32_t i = 0; i < pMeterMeta->numOfTags + pMeterMeta->numOfColumns; ++i) {
    if (strncasecmp(pColField->name, pSchema[i].name, TSDB_COL_NAME_LEN) == 0) {
      setErrMsg(pCmd, msg2);
      return false;
    }
  }

  return true;
}