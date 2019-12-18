#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* nativSql; } ;
struct TYPE_8__ {char* pos; } ;
struct TYPE_9__ {TYPE_1__ data; } ;
struct TYPE_11__ {int /*<<< orphan*/ * encodeMethod; int /*<<< orphan*/  reqType; TYPE_3__ singleCmd; TYPE_2__ parser; int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ HttpSqlCmd ;
typedef  TYPE_4__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_NO_EXEC_USEDB ; 
 int /*<<< orphan*/  HTTP_NO_SQL_INPUT ; 
 int /*<<< orphan*/  HTTP_REQTYPE_SINGLE_SQL ; 
 int REST_TIMESTAMP_FMT_LOCAL_STRING ; 
 int REST_TIMESTAMP_FMT_TIMESTAMP ; 
 int REST_TIMESTAMP_FMT_UTC_STRING ; 
 scalar_t__ httpCheckUsedbSql (char*) ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restEncodeSqlLocalTimeStringMethod ; 
 int /*<<< orphan*/  restEncodeSqlTimestampMethod ; 
 int /*<<< orphan*/  restEncodeSqlUtcTimeStringMethod ; 

bool restProcessSqlRequest(HttpContext* pContext, int timestampFmt) {
  httpTrace("context:%p, fd:%d, ip:%s, user:%s, process restful sql msg", pContext, pContext->fd, pContext->ipstr,
            pContext->user);

  char* sql = pContext->parser.data.pos;
  if (sql == NULL) {
    httpSendErrorResp(pContext, HTTP_NO_SQL_INPUT);
    return false;
  }

  if (httpCheckUsedbSql(sql)) {
    httpSendErrorResp(pContext, HTTP_NO_EXEC_USEDB);
    return false;
  }

  HttpSqlCmd* cmd = &(pContext->singleCmd);
  cmd->nativSql = sql;

  pContext->reqType = HTTP_REQTYPE_SINGLE_SQL;
  if (timestampFmt == REST_TIMESTAMP_FMT_LOCAL_STRING) {
    pContext->encodeMethod = &restEncodeSqlLocalTimeStringMethod;
  } else if (timestampFmt == REST_TIMESTAMP_FMT_TIMESTAMP) {
    pContext->encodeMethod = &restEncodeSqlTimestampMethod;
  } else if (timestampFmt == REST_TIMESTAMP_FMT_UTC_STRING) {
    pContext->encodeMethod = &restEncodeSqlUtcTimeStringMethod;
  }

  return true;
}