#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * session; int /*<<< orphan*/ * taos; int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; struct TYPE_9__* signature; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_NO_ENOUGH_SESSIONS ; 
 int /*<<< orphan*/  HTTP_SESSION_FULL ; 
 int /*<<< orphan*/  httpCloseContextByApp (TYPE_1__*) ; 
 int /*<<< orphan*/  httpCreateSession (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpError (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  httpExecCmd (TYPE_1__*) ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpSendTaosdErrorResp (TYPE_1__*,int) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void httpProcessRequestCb(void *param, TAOS_RES *result, int code) {
  HttpContext *pContext = param;
  if (pContext == NULL || pContext->signature != pContext) return;

  if (code < 0) {
    httpError("context:%p, fd:%d, ip:%s, user:%s, login error, code:%d", pContext, pContext->fd, pContext->ipstr,
              pContext->user, -code);
    httpSendTaosdErrorResp(pContext, -code);
    return;
  }

  httpTrace("context:%p, fd:%d, ip:%s, user:%s, connect tdengine success, taos:%p", pContext, pContext->fd,
            pContext->ipstr, pContext->user, pContext->taos);
  if (pContext->taos == NULL) {
    httpError("context:%p, fd:%d, ip:%s, user:%s, login error, taos is empty", pContext, pContext->fd, pContext->ipstr,
              pContext->user);
    httpSendErrorResp(pContext, HTTP_NO_ENOUGH_SESSIONS);
    return;
  }

  httpCreateSession(pContext, pContext->taos);

  if (pContext->session == NULL) {
    httpSendErrorResp(pContext, HTTP_SESSION_FULL);
    httpCloseContextByApp(pContext);
  } else {
    httpExecCmd(pContext);
  }
}