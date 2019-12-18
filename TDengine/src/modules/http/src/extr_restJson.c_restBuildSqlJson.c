#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_12__ {scalar_t__ fd; int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; } ;
struct TYPE_11__ {scalar_t__ numOfRows; } ;
struct TYPE_10__ {int type; int /*<<< orphan*/  bytes; } ;
typedef  int /*<<< orphan*/ ** TAOS_ROW ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ TAOS_FIELD ;
typedef  int /*<<< orphan*/  JsonBuf ;
typedef  TYPE_2__ HttpSqlCmd ;
typedef  TYPE_3__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  JsonArrEnd ; 
 int /*<<< orphan*/  JsonArrStt ; 
 int REST_TIMESTAMP_FMT_LOCAL_STRING ; 
 int REST_TIMESTAMP_FMT_TIMESTAMP ; 
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
 int /*<<< orphan*/  TSDB_TIME_PRECISION_MICRO ; 
 int /*<<< orphan*/  httpError (char*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpJsonDouble (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  httpJsonFloat (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  httpJsonInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpJsonInt64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpJsonItemToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpJsonOriginString (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  httpJsonStringForTransMean (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpJsonTimestamp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  httpJsonToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpJsonUtcTimestamp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * httpMallocJsonBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,...) ; 
 TYPE_1__* taos_fetch_fields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** taos_fetch_row (int /*<<< orphan*/ *) ; 
 int taos_num_fields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_result_precision (int /*<<< orphan*/ *) ; 
 scalar_t__ tsRestRowLimit ; 

bool restBuildSqlJson(HttpContext *pContext, HttpSqlCmd *cmd, TAOS_RES *result, int numOfRows, int timestampFormat) {
  JsonBuf *jsonBuf = httpMallocJsonBuf(pContext);
  if (jsonBuf == NULL) return false;

  cmd->numOfRows += numOfRows;

  int         num_fields = taos_num_fields(result);
  TAOS_FIELD *fields = taos_fetch_fields(result);

  for (int i = 0; i < numOfRows; ++i) {
    TAOS_ROW row = taos_fetch_row(result);

    // data row array begin
    httpJsonItemToken(jsonBuf);
    httpJsonToken(jsonBuf, JsonArrStt);

    for (int i = 0; i < num_fields; i++) {
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
          if (timestampFormat == REST_TIMESTAMP_FMT_LOCAL_STRING) {
            httpJsonTimestamp(jsonBuf, *((int64_t *)row[i]), taos_result_precision(result) == TSDB_TIME_PRECISION_MICRO);
          } else if (timestampFormat == REST_TIMESTAMP_FMT_TIMESTAMP) {
            httpJsonInt64(jsonBuf, *((int64_t *)row[i]));
          } else {
            httpJsonUtcTimestamp(jsonBuf, *((int64_t *)row[i]), taos_result_precision(result) == TSDB_TIME_PRECISION_MICRO);
          }
          break;
        default:
          break;
      }
    }

    // data row array end
    httpJsonToken(jsonBuf, JsonArrEnd);
  }

  if (cmd->numOfRows >= tsRestRowLimit) {
    httpTrace("context:%p, fd:%d, ip:%s, user:%s, retrieve rows:%lld larger than limit:%d, abort retrieve", pContext,
              pContext->fd, pContext->ipstr, pContext->user, cmd->numOfRows, tsRestRowLimit);
    return false;
  }
  else {
    if (pContext->fd <= 0) {
      httpError("context:%p, fd:%d, ip:%s, user:%s, connection is closed, abort retrieve", pContext, pContext->fd,
                pContext->ipstr, pContext->user);
      return false;
    }
    else {
      httpTrace("context:%p, fd:%d, ip:%s, user:%s, total rows:%lld retrieved", pContext, pContext->fd, pContext->ipstr,
                pContext->user, cmd->numOfRows);
      return true;
    }
  }
}