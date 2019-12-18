#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* session; int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_4__* encodeMethod; TYPE_2__* multiCmds; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* cleanJsonFp ) (TYPE_5__*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  sql; } ;
struct TYPE_13__ {scalar_t__ pos; scalar_t__ size; TYPE_3__* cmds; } ;
struct TYPE_12__ {int /*<<< orphan*/  taos; } ;
typedef  TYPE_2__ HttpSqlCmds ;
typedef  TYPE_3__ HttpSqlCmd ;
typedef  TYPE_4__ HttpEncodeMethod ;
typedef  TYPE_5__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  httpCloseContextByApp (TYPE_5__*) ; 
 int /*<<< orphan*/  httpDump (char*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 char* httpGetCmdsString (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpProcessMultiSqlCallBack ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  taosNotePrint (char*) ; 
 int /*<<< orphan*/  taos_query_a (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 

void httpProcessMultiSql(HttpContext *pContext) {
  HttpSqlCmds *     multiCmds = pContext->multiCmds;
  HttpEncodeMethod *encode = pContext->encodeMethod;

  if (multiCmds->pos >= multiCmds->size) {
    httpTrace("context:%p, fd:%d, ip:%s, user:%s, process pos:%d, size:%d, stop mulit-querys",
              pContext, pContext->fd, pContext->ipstr, pContext->user, multiCmds->pos, multiCmds->size);
    if (encode->cleanJsonFp) {
      (encode->cleanJsonFp)(pContext);
    }
    httpCloseContextByApp(pContext);
    return;
  }

  HttpSqlCmd *cmd = multiCmds->cmds + multiCmds->pos;

  char *sql = httpGetCmdsString(pContext, cmd->sql);
  httpDump("context:%p, fd:%d, ip:%s, user:%s, process pos:%d, start query, sql:%s", pContext, pContext->fd,
           pContext->ipstr, pContext->user, multiCmds->pos, sql);
  taosNotePrint(sql);
  taos_query_a(pContext->session->taos, sql, httpProcessMultiSqlCallBack, (void *)pContext);
}