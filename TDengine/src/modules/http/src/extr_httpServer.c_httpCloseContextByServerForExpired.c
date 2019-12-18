#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pThread; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_PARSE_BODY_ERROR ; 
 int /*<<< orphan*/  httpCloseContextByServer (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  httpError (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  httpRemoveContextFromEpoll (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_1__*,int /*<<< orphan*/ ) ; 

void httpCloseContextByServerForExpired(void *param, void *tmrId) {
  HttpContext *pContext = (HttpContext *)param;
  httpRemoveContextFromEpoll(pContext->pThread, pContext);
  httpError("context:%p, fd:%d, ip:%s, read http body error, time expired, timer:%p", pContext, pContext->fd, pContext->ipstr, tmrId);
  httpSendErrorResp(pContext, HTTP_PARSE_BODY_ERROR);
  httpCloseContextByServer(pContext->pThread, pContext);
}