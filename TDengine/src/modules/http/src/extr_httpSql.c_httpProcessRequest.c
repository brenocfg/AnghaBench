#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ reqType; int /*<<< orphan*/  taos; int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; int /*<<< orphan*/  pass; TYPE_1__* session; } ;
struct TYPE_8__ {struct TYPE_8__* signature; } ;
typedef  TYPE_2__ HttpContext ;

/* Variables and functions */
 scalar_t__ HTTP_REQTYPE_LOGIN ; 
 int /*<<< orphan*/  httpAccessSession (TYPE_2__*) ; 
 int /*<<< orphan*/  httpExecCmd (TYPE_2__*) ; 
 int /*<<< orphan*/  httpFetchSession (TYPE_2__*) ; 
 int /*<<< orphan*/  httpProcessRequestCb ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_connect_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

void httpProcessRequest(HttpContext *pContext) {
  if (pContext->session == NULL) {
    httpFetchSession(pContext);
  }

  if (pContext->session == NULL || pContext->session != pContext->session->signature ||
      pContext->reqType == HTTP_REQTYPE_LOGIN) {
    taos_connect_a(NULL, pContext->user, pContext->pass, "", 0, httpProcessRequestCb, (void *)pContext,
                   &(pContext->taos));
    httpTrace("context:%p, fd:%d, ip:%s, user:%s, try connect tdengine, taos:%p", pContext, pContext->fd,
              pContext->ipstr, pContext->user, pContext->taos);
  } else {
    httpAccessSession(pContext);
    httpExecCmd(pContext);
  }
}