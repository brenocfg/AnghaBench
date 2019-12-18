#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_3__* encodeMethod; TYPE_1__* multiCmds; struct TYPE_16__* signature; } ;
struct TYPE_15__ {int (* buildQueryJsonFp ) (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* stopJsonFp ) (TYPE_4__*,TYPE_2__*) ;} ;
struct TYPE_14__ {scalar_t__ cmdReturnType; int /*<<< orphan*/  sql; } ;
struct TYPE_13__ {int pos; TYPE_2__* cmds; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ HttpSqlCmds ;
typedef  TYPE_2__ HttpSqlCmd ;
typedef  TYPE_3__ HttpEncodeMethod ;
typedef  TYPE_4__ HttpContext ;

/* Variables and functions */
 scalar_t__ HTTP_CMD_RETURN_TYPE_WITH_RETURN ; 
 int /*<<< orphan*/  httpError (char*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 char* httpGetCmdsString (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpProcessMultiSql (TYPE_4__*) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 int stub1 (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  taos_fetch_rows_a (int /*<<< orphan*/ *,void (*) (void*,int /*<<< orphan*/ *,int),void*) ; 
 int /*<<< orphan*/  taos_free_result (int /*<<< orphan*/ *) ; 

void httpProcessMultiSqlRetrieveCallBack(void *param, TAOS_RES *result, int numOfRows) {
  HttpContext *pContext = (HttpContext *)param;
  if (pContext == NULL || pContext->signature != pContext) return;

  HttpSqlCmds *     multiCmds = pContext->multiCmds;
  HttpEncodeMethod *encode = pContext->encodeMethod;

  HttpSqlCmd *singleCmd = multiCmds->cmds + multiCmds->pos;
  char *      sql = httpGetCmdsString(pContext, singleCmd->sql);

  bool isContinue = false;

  if (numOfRows > 0) {
    if (singleCmd->cmdReturnType == HTTP_CMD_RETURN_TYPE_WITH_RETURN && encode->buildQueryJsonFp) {
      isContinue = (encode->buildQueryJsonFp)(pContext, singleCmd, result, numOfRows);
    }
  }

  if (isContinue) {
    // retrieve next batch of rows
    httpTrace("context:%p, fd:%d, ip:%s, user:%s, process pos:%d, continue retrieve, numOfRows:%d, sql:%s",
              pContext, pContext->fd, pContext->ipstr, pContext->user, multiCmds->pos, numOfRows, sql);
    taos_fetch_rows_a(result, httpProcessMultiSqlRetrieveCallBack, param);
  } else {
    httpTrace("context:%p, fd:%d, ip:%s, user:%s, process pos:%d, stop retrieve, numOfRows:%d, sql:%s",
              pContext, pContext->fd, pContext->ipstr, pContext->user, multiCmds->pos, numOfRows, sql);

    if (numOfRows < 0) {
      httpError("context:%p, fd:%d, ip:%s, user:%s, process pos:%d, retrieve failed code:%d, sql:%s",
                pContext, pContext->fd, pContext->ipstr, pContext->user, multiCmds->pos, -numOfRows, sql);
    } else {
      taos_free_result(result);
    }

    if (singleCmd->cmdReturnType == HTTP_CMD_RETURN_TYPE_WITH_RETURN && encode->stopJsonFp) {
      (encode->stopJsonFp)(pContext, singleCmd);
    }
    multiCmds->pos++;
    httpProcessMultiSql(pContext);
  }
}