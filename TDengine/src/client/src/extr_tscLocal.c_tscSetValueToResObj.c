#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int int8_t ;
typedef  char* int64_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_22__ {int numOfColumns; int numOfTags; } ;
struct TYPE_21__ {TYPE_6__* pMeterMeta; } ;
struct TYPE_20__ {char* name; size_t type; int bytes; } ;
struct TYPE_18__ {char* data; } ;
struct TYPE_19__ {int /*<<< orphan*/  cmd; TYPE_2__ res; } ;
struct TYPE_17__ {int bytes; } ;
struct TYPE_16__ {char* aName; } ;
typedef  TYPE_1__ TAOS_FIELD ;
typedef  TYPE_2__ SSqlRes ;
typedef  TYPE_3__ SSqlObj ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_4__ SSchema ;
typedef  TYPE_5__ SMeterMetaInfo ;
typedef  TYPE_6__ SMeterMeta ;

/* Variables and functions */
 int TSDB_COL_NAME_LEN ; 
 char* TSDB_DATA_NULL_STR ; 
#define  TSDB_DATA_TYPE_BIGINT 136 
#define  TSDB_DATA_TYPE_BINARY 135 
#define  TSDB_DATA_TYPE_BOOL 134 
#define  TSDB_DATA_TYPE_DOUBLE 133 
#define  TSDB_DATA_TYPE_FLOAT 132 
#define  TSDB_DATA_TYPE_INT 131 
#define  TSDB_DATA_TYPE_NCHAR 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int TSDB_NCHAR_SIZE ; 
 scalar_t__ UTIL_METER_IS_METRIC (TYPE_5__*) ; 
 scalar_t__ isNull (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 TYPE_14__* tDataTypeDesc ; 
 int /*<<< orphan*/  taosUcs4ToMbs (char*,int,char*) ; 
 TYPE_4__* tsGetSchema (TYPE_6__*) ; 
 char* tsGetTagsValue (TYPE_6__*) ; 
 TYPE_1__* tscFieldInfoGetField (int /*<<< orphan*/ *,int) ; 
 int tscFieldInfoGetOffset (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscInitResObjForLocalQuery (TYPE_3__*,int,int) ; 

__attribute__((used)) static int32_t tscSetValueToResObj(SSqlObj *pSql, int32_t rowLen) {
  SSqlRes *pRes = &pSql->res;

  // one column for each row
  SSqlCmd *       pCmd = &pSql->cmd;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);
  SMeterMeta *    pMeta = pMeterMetaInfo->pMeterMeta;

  /*
   * tagValueCnt is to denote the number of tags columns for meter, not metric. and is to show the column data.
   * for meter, which is created according to metric, the value of tagValueCnt is not 0, and the numOfTags must be 0.
   * for metric, the value of tagValueCnt must be 0, but the numOfTags is not 0
   */

  int32_t numOfRows = pMeta->numOfColumns;
  int32_t totalNumOfRows = numOfRows + pMeta->numOfTags;

  if (UTIL_METER_IS_METRIC(pMeterMetaInfo)) {
    numOfRows = pMeta->numOfColumns + pMeta->numOfTags;
  }

  tscInitResObjForLocalQuery(pSql, totalNumOfRows, rowLen);
  SSchema *pSchema = tsGetSchema(pMeta);

  for (int32_t i = 0; i < numOfRows; ++i) {
    TAOS_FIELD *pField = tscFieldInfoGetField(pCmd, 0);
    strncpy(pRes->data + tscFieldInfoGetOffset(pCmd, 0) * totalNumOfRows + pField->bytes * i, pSchema[i].name,
            TSDB_COL_NAME_LEN);

    char *type = tDataTypeDesc[pSchema[i].type].aName;

    pField = tscFieldInfoGetField(pCmd, 1);
    strncpy(pRes->data + tscFieldInfoGetOffset(pCmd, 1) * totalNumOfRows + pField->bytes * i, type, pField->bytes);

    int32_t bytes = pSchema[i].bytes;
    if (pSchema[i].type == TSDB_DATA_TYPE_NCHAR) {
      bytes = bytes / TSDB_NCHAR_SIZE;
    }

    pField = tscFieldInfoGetField(pCmd, 2);
    *(int32_t *)(pRes->data + tscFieldInfoGetOffset(pCmd, 2) * totalNumOfRows + pField->bytes * i) = bytes;

    pField = tscFieldInfoGetField(pCmd, 3);
    if (i >= pMeta->numOfColumns && pMeta->numOfTags != 0) {
      strncpy(pRes->data + tscFieldInfoGetOffset(pCmd, 3) * totalNumOfRows + pField->bytes * i, "tag",
              strlen("tag") + 1);
    }
  }

  if (UTIL_METER_IS_METRIC(pMeterMetaInfo)) {
    return 0;
  }

  // the following is handle display tags value for meters created according to metric
  char *pTagValue = tsGetTagsValue(pMeta);
  for (int32_t i = numOfRows; i < totalNumOfRows; ++i) {
    // field name
    TAOS_FIELD *pField = tscFieldInfoGetField(pCmd, 0);
    strncpy(pRes->data + tscFieldInfoGetOffset(pCmd, 0) * totalNumOfRows + pField->bytes * i, pSchema[i].name,
            TSDB_COL_NAME_LEN);

    // type name
    pField = tscFieldInfoGetField(pCmd, 1);
    char *type = tDataTypeDesc[pSchema[i].type].aName;
    strncpy(pRes->data + tscFieldInfoGetOffset(pCmd, 1) * totalNumOfRows + pField->bytes * i, type, pField->bytes);

    // type length
    int32_t bytes = pSchema[i].bytes;
    pField = tscFieldInfoGetField(pCmd, 2);
    if (pSchema[i].type == TSDB_DATA_TYPE_NCHAR) {
      bytes = bytes / TSDB_NCHAR_SIZE;
    }

    *(int32_t *)(pRes->data + tscFieldInfoGetOffset(pCmd, 2) * totalNumOfRows + pField->bytes * i) = bytes;

    // tag value
    pField = tscFieldInfoGetField(pCmd, 3);
    char *target = pRes->data + tscFieldInfoGetOffset(pCmd, 3) * totalNumOfRows + pField->bytes * i;

    if (isNull(pTagValue, pSchema[i].type)) {
      sprintf(target, "%s", TSDB_DATA_NULL_STR);
    } else {
      switch (pSchema[i].type) {
        case TSDB_DATA_TYPE_BINARY:
          /* binary are not null-terminated string */
          strncpy(target, pTagValue, pSchema[i].bytes);
          break;
        case TSDB_DATA_TYPE_NCHAR:
          taosUcs4ToMbs(pTagValue, pSchema[i].bytes, target);
          break;
        case TSDB_DATA_TYPE_FLOAT: {
#ifdef _TD_ARM_32_
          float fv = 0;
          *(int32_t*)(&fv) = *(int32_t*)pTagValue;
          sprintf(target, "%f", fv);
#else
          sprintf(target, "%f", *(float *)pTagValue);
#endif
          }
          break;
        case TSDB_DATA_TYPE_DOUBLE: {
#ifdef _TD_ARM_32_
          double dv = 0;
          *(int64_t*)(&dv) = *(int64_t*)pTagValue;
          sprintf(target, "%lf", dv);
#else
          sprintf(target, "%lf", *(double *)pTagValue);
#endif
          }
          break;
        case TSDB_DATA_TYPE_TINYINT:
          sprintf(target, "%d", *(int8_t *)pTagValue);
          break;
        case TSDB_DATA_TYPE_SMALLINT:
          sprintf(target, "%d", *(int16_t *)pTagValue);
          break;
        case TSDB_DATA_TYPE_INT:
          sprintf(target, "%d", *(int32_t *)pTagValue);
          break;
        case TSDB_DATA_TYPE_BIGINT:
          sprintf(target, "%lld", *(int64_t *)pTagValue);
          break;
        case TSDB_DATA_TYPE_BOOL: {
          char *val = (*((int8_t *)pTagValue) == 0) ? "false" : "true";
          sprintf(target, "%s", val);
          break;
        }
        default:
          break;
      }
    }

    pTagValue += pSchema[i].bytes;
  }

  return 0;
}