#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ TAOS_FIELD ;
typedef  int /*<<< orphan*/  JsonBuf ;
typedef  int /*<<< orphan*/  HttpSqlCmd ;
typedef  int /*<<< orphan*/  HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  JsonArrEnd ; 
 int /*<<< orphan*/  JsonArrStt ; 
 int /*<<< orphan*/  JsonObjStt ; 
 int /*<<< orphan*/  REST_JSON_AFFECT_ROWS ; 
 int REST_JSON_AFFECT_ROWS_LEN ; 
 int /*<<< orphan*/  REST_JSON_DATA ; 
 int /*<<< orphan*/  REST_JSON_DATA_LEN ; 
 int /*<<< orphan*/  REST_JSON_HEAD ; 
 int /*<<< orphan*/  REST_JSON_HEAD_LEN ; 
 int /*<<< orphan*/  REST_JSON_STATUS ; 
 int /*<<< orphan*/  REST_JSON_STATUS_LEN ; 
 int /*<<< orphan*/  REST_JSON_SUCCESS ; 
 int /*<<< orphan*/  REST_JSON_SUCCESS_LEN ; 
 int /*<<< orphan*/  httpInitJsonBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpJsonItemToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpJsonPair (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpJsonPairHead (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpJsonString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  httpJsonToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * httpMallocJsonBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpWriteJsonBufHead (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 TYPE_1__* taos_fetch_fields (int /*<<< orphan*/ *) ; 
 int taos_num_fields (int /*<<< orphan*/ *) ; 

void restStartSqlJson(HttpContext *pContext, HttpSqlCmd *cmd, TAOS_RES *result) {
  JsonBuf *jsonBuf = httpMallocJsonBuf(pContext);
  if (jsonBuf == NULL) return;

  TAOS_FIELD *fields = taos_fetch_fields(result);
  int         num_fields = taos_num_fields(result);

  httpInitJsonBuf(jsonBuf, pContext);
  httpWriteJsonBufHead(jsonBuf);

  // object begin
  httpJsonToken(jsonBuf, JsonObjStt);

  // status, and data
  httpJsonItemToken(jsonBuf);
  httpJsonPair(jsonBuf, REST_JSON_STATUS, REST_JSON_STATUS_LEN, REST_JSON_SUCCESS, REST_JSON_SUCCESS_LEN);

  // head begin
  httpJsonItemToken(jsonBuf);
  httpJsonPairHead(jsonBuf, REST_JSON_HEAD, REST_JSON_HEAD_LEN);
  // head array begin
  httpJsonItemToken(jsonBuf);
  httpJsonToken(jsonBuf, JsonArrStt);

  if (num_fields == 0) {
    httpJsonItemToken(jsonBuf);
    httpJsonString(jsonBuf, REST_JSON_AFFECT_ROWS, REST_JSON_AFFECT_ROWS_LEN);
  } else {
    for (int i = 0; i < num_fields; ++i) {
      httpJsonItemToken(jsonBuf);
      httpJsonString(jsonBuf, fields[i].name, (int)strlen(fields[i].name));
    }
  }

  // head array end
  httpJsonToken(jsonBuf, JsonArrEnd);

  // data begin
  httpJsonItemToken(jsonBuf);
  httpJsonPairHead(jsonBuf, REST_JSON_DATA, REST_JSON_DATA_LEN);
  // data array begin
  httpJsonItemToken(jsonBuf);
  httpJsonToken(jsonBuf, JsonArrStt);
}