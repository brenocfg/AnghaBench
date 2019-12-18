#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  state; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; } ;
struct TYPE_9__ {TYPE_1__* pServer; } ;
struct TYPE_8__ {int /*<<< orphan*/  timerHandle; } ;
typedef  TYPE_2__ HttpThread ;
typedef  TYPE_3__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_DELAY_CLOSE_TIME_MS ; 
 int /*<<< orphan*/  httpCleanUpContext ; 
 int /*<<< orphan*/  httpContextStateStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void httpCloseContext(HttpThread *pThread, HttpContext *pContext) {
  taosTmrReset(httpCleanUpContext, HTTP_DELAY_CLOSE_TIME_MS, pContext, pThread->pServer->timerHandle, &pContext->timer);
  httpTrace("context:%p, fd:%d, ip:%s, state:%s will be closed after:%d ms, timer:%p",
          pContext, pContext->fd, pContext->ipstr, httpContextStateStr(pContext->state), HTTP_DELAY_CLOSE_TIME_MS, pContext->timer);
}