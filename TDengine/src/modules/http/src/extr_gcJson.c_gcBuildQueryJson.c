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
typedef  char* int8_t ;
typedef  int int64_t ;
typedef  char* int32_t ;
typedef  char* int16_t ;
struct TYPE_6__ {scalar_t__ numOfRows; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  table; int /*<<< orphan*/  values; } ;
struct TYPE_5__ {int type; int /*<<< orphan*/  bytes; } ;
typedef  int /*<<< orphan*/ ** TAOS_ROW ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ TAOS_FIELD ;
typedef  int /*<<< orphan*/  JsonBuf ;
typedef  TYPE_2__ HttpSqlCmd ;
typedef  int /*<<< orphan*/  HttpContext ;

/* Variables and functions */
 int HTTP_GC_TARGET_SIZE ; 
 int /*<<< orphan*/  JsonArrEnd ; 
 int /*<<< orphan*/  JsonArrStt ; 
#define  TSDB_DATA_TYPE_BIGINT 137 
#define  TSDB_DATA_TYPE_BINARY 136 
#define  TSDB_DATA_TYPE_BOOL 135 
#define  TSDB_DATA_TYPE_DOUBLE 134 
#define  TSDB_DATA_TYPE_FLOAT 133 
#define  TSDB_DATA_TYPE_INT 132 
#define  TSDB_DATA_TYPE_NCHAR 131 
#define  TSDB_DATA_TYPE_SMALLINT 130 
#define  TSDB_DATA_TYPE_TIMESTAMP 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int TSDB_TIME_PRECISION_MILLI ; 
 int /*<<< orphan*/  gcWriteTargetEndJson (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcWriteTargetStartJson (int /*<<< orphan*/ *,char*,char*) ; 
 char* httpGetCmdsString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpJsonDouble (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  httpJsonFloat (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  httpJsonInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  httpJsonInt64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  httpJsonItemToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpJsonOriginString (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  httpJsonString (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  httpJsonStringForTransMean (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpJsonToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * httpMallocJsonBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 TYPE_1__* taos_fetch_fields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** taos_fetch_row (int /*<<< orphan*/ *) ; 
 int taos_num_fields (int /*<<< orphan*/ *) ; 
 int taos_result_precision (int /*<<< orphan*/ *) ; 

bool gcBuildQueryJson(HttpContext *pContext, HttpSqlCmd *cmd, TAOS_RES *result, int numOfRows) {
  JsonBuf *jsonBuf = httpMallocJsonBuf(pContext);
  if (jsonBuf == NULL) return false;

  int         num_fields = taos_num_fields(result);
  TAOS_FIELD *fields = taos_fetch_fields(result);
  if (num_fields == 0) {
    return false;
  }

  int precision = taos_result_precision(result);

  // such as select count(*) from sys.cpu
  // such as select count(*) from sys.cpu group by ipaddr
  // such as select count(*) from sys.cpu interval(1d)
  // such as select count(*) from sys.cpu interval(1d) group by ipaddr
  // such as select count(*) count(*) from sys.cpu group by ipaddr interval(1d)
  int  dataFields = -1;
  int  groupFields = -1;
  bool hasTimestamp = fields[0].type == TSDB_DATA_TYPE_TIMESTAMP;
  if (hasTimestamp) {
    dataFields = 1;
    if (num_fields > 2) groupFields = num_fields - 1;
  } else {
    dataFields = 0;
    if (num_fields > 1) groupFields = num_fields - 1;
  }

  char *refIdBuffer = httpGetCmdsString(pContext, cmd->values);
  char *aliasBuffer = httpGetCmdsString(pContext, cmd->table);
  char *targetBuffer = httpGetCmdsString(pContext, cmd->timestamp);

  if (groupFields == -1 && cmd->numOfRows == 0) {
    gcWriteTargetStartJson(jsonBuf, refIdBuffer, aliasBuffer);
    cmd->numOfRows += numOfRows;
  }

  for (int i = 0; i < numOfRows; ++i) {
    TAOS_ROW row = taos_fetch_row(result);

    // for group by
    if (groupFields != -1) {
      char target[HTTP_GC_TARGET_SIZE];

      switch (fields[groupFields].type) {
        case TSDB_DATA_TYPE_BOOL:
        case TSDB_DATA_TYPE_TINYINT:
          snprintf(target, HTTP_GC_TARGET_SIZE, "%s%d", aliasBuffer, *((int8_t *)row[groupFields]));
          break;
        case TSDB_DATA_TYPE_SMALLINT:
          snprintf(target, HTTP_GC_TARGET_SIZE, "%s%d", aliasBuffer, *((int16_t *)row[groupFields]));
          break;
        case TSDB_DATA_TYPE_INT:
          snprintf(target, HTTP_GC_TARGET_SIZE, "%s%d", aliasBuffer, *((int32_t *)row[groupFields]));
          break;
        case TSDB_DATA_TYPE_BIGINT:
          snprintf(target, HTTP_GC_TARGET_SIZE, "%s%ld", aliasBuffer, *((int64_t *)row[groupFields]));
          break;
        case TSDB_DATA_TYPE_FLOAT:
          snprintf(target, HTTP_GC_TARGET_SIZE, "%s%.5f", aliasBuffer, *((float *)row[groupFields]));
          break;
        case TSDB_DATA_TYPE_DOUBLE:
          snprintf(target, HTTP_GC_TARGET_SIZE, "%s%.9f", aliasBuffer, *((double *)row[groupFields]));
          break;
        case TSDB_DATA_TYPE_BINARY:
        case TSDB_DATA_TYPE_NCHAR:
          snprintf(target, HTTP_GC_TARGET_SIZE, "%s%s", aliasBuffer, (char *)row[groupFields]);
          break;
        case TSDB_DATA_TYPE_TIMESTAMP:
          if (precision == TSDB_TIME_PRECISION_MILLI) {
            snprintf(target, HTTP_GC_TARGET_SIZE, "%s%ld", aliasBuffer, *((int64_t *) row[groupFields]));
          } else {
            snprintf(target, HTTP_GC_TARGET_SIZE, "%s%ld", aliasBuffer, *((int64_t *) row[groupFields]) / 1000);
          }
          break;
        default:
          snprintf(target, HTTP_GC_TARGET_SIZE, "%s%s", aliasBuffer, "invalidcol");
          break;
      }

      if (strcmp(target, targetBuffer) != 0) {
        // first target not write this section
        if (strlen(targetBuffer) != 0) {
          gcWriteTargetEndJson(jsonBuf);
        }

        // start new target
        gcWriteTargetStartJson(jsonBuf, refIdBuffer, target);
        strncpy(targetBuffer, target, HTTP_GC_TARGET_SIZE);
      }
    }  // end of group by

    // data row array begin
    httpJsonItemToken(jsonBuf);
    httpJsonToken(jsonBuf, JsonArrStt);

    for (int i = dataFields; i >= 0; i--) {
      httpJsonItemToken(jsonBuf);
      if (row[i] == NULL) {
        httpJsonOriginString(jsonBuf, "null", 4);
        continue;
      }

      switch (fields[i].type) {
        case TSDB_DATA_TYPE_BOOL:
        case TSDB_DATA_TYPE_TINYINT:
          httpJsonInt(jsonBuf, *((int8_t *)row[i]));
          break;
        case TSDB_DATA_TYPE_SMALLINT:
          httpJsonInt(jsonBuf, *((int16_t *)row[i]));
          break;
        case TSDB_DATA_TYPE_INT:
          httpJsonInt(jsonBuf, *((int32_t *)row[i]));
          break;
        case TSDB_DATA_TYPE_BIGINT:
          httpJsonInt64(jsonBuf, *((int64_t *)row[i]));
          break;
        case TSDB_DATA_TYPE_FLOAT:
          httpJsonFloat(jsonBuf, *((float *)row[i]));
          break;
        case TSDB_DATA_TYPE_DOUBLE:
          httpJsonDouble(jsonBuf, *((double *)row[i]));
          break;
        case TSDB_DATA_TYPE_BINARY:
        case TSDB_DATA_TYPE_NCHAR:
          httpJsonStringForTransMean(jsonBuf, row[i], fields[i].bytes);
          break;
        case TSDB_DATA_TYPE_TIMESTAMP:
          if (precision == TSDB_TIME_PRECISION_MILLI) { //ms
            httpJsonInt64(jsonBuf, *((int64_t *)row[i]));
          } else {
            httpJsonInt64(jsonBuf, *((int64_t *)row[i]) / 1000);
          }
          break;
        default:
          httpJsonString(jsonBuf, "invalidcol", 10);
          break;
      }
    }

    if (dataFields == 0) {
      httpJsonItemToken(jsonBuf);
      httpJsonString(jsonBuf, "-", 1);
    }

    // data row array end
    httpJsonToken(jsonBuf, JsonArrEnd);
  }

  return true;
}