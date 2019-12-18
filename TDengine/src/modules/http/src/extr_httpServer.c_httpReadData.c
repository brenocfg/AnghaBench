#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; int /*<<< orphan*/  timer; int /*<<< orphan*/  parsed; } ;
struct TYPE_18__ {TYPE_1__* pServer; } ;
struct TYPE_17__ {int /*<<< orphan*/  timerHandle; } ;
typedef  TYPE_2__ HttpThread ;
typedef  TYPE_3__ HttpContext ;

/* Variables and functions */
 int HTTP_CHECK_BODY_CONTINUE ; 
 int HTTP_CHECK_BODY_SUCCESS ; 
 int /*<<< orphan*/  HTTP_EXPIRED_TIME ; 
 int httpCheckReadCompleted (TYPE_3__*) ; 
 int /*<<< orphan*/  httpCleanUpContextTimer (TYPE_3__*) ; 
 int /*<<< orphan*/  httpCloseContextByServer (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  httpCloseContextByServerForExpired ; 
 scalar_t__ httpDecompressData (TYPE_3__*) ; 
 int /*<<< orphan*/  httpError (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpInitContext (TYPE_3__*) ; 
 int /*<<< orphan*/  httpParseRequest (TYPE_3__*) ; 
 int /*<<< orphan*/  httpReadDataImp (TYPE_3__*) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool httpReadData(HttpThread *pThread, HttpContext *pContext) {
  if (!pContext->parsed) {
    httpInitContext(pContext);
  }

  if (!httpReadDataImp(pContext)) {
    httpCloseContextByServer(pThread, pContext);
    return false;
  }

  if (!httpParseRequest(pContext)) {
    httpCloseContextByServer(pThread, pContext);
    return false;
  }

  int ret = httpCheckReadCompleted(pContext);
  if (ret == HTTP_CHECK_BODY_CONTINUE) {
    taosTmrReset(httpCloseContextByServerForExpired, HTTP_EXPIRED_TIME, pContext, pThread->pServer->timerHandle, &pContext->timer);
    httpTrace("context:%p, fd:%d, ip:%s, not finished yet, try another times, timer:%p", pContext, pContext->fd, pContext->ipstr, pContext->timer);
    return false;
  } else if (ret == HTTP_CHECK_BODY_SUCCESS){
    httpCleanUpContextTimer(pContext);
    if (httpDecompressData(pContext)) {
      return true;
    } else {
      httpCloseContextByServer(pThread, pContext);
      return false;
    }
  } else {
    httpCleanUpContextTimer(pContext);
    httpError("context:%p, fd:%d, ip:%s, failed to read http body, close connect", pContext, pContext->fd, pContext->ipstr);
    httpCloseContextByServer(pThread, pContext);
    return false;
  }
}