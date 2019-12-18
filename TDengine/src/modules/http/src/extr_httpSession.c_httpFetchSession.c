#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_2__* session; TYPE_1__* pThread; } ;
struct TYPE_9__ {int /*<<< orphan*/  serverMutex; scalar_t__ sessionExpire; int /*<<< orphan*/  pSessionHash; } ;
struct TYPE_8__ {scalar_t__ expire; int /*<<< orphan*/  access; int /*<<< orphan*/  taos; int /*<<< orphan*/  id; struct TYPE_8__* signature; } ;
struct TYPE_7__ {TYPE_3__* pServer; } ;
typedef  TYPE_2__ HttpSession ;
typedef  TYPE_3__ HttpServer ;
typedef  TYPE_4__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  httpTrace (char*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ taosGetStrHashData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ taosGetTimestampSec () ; 

void httpFetchSession(HttpContext *pContext) {
  HttpServer *server = pContext->pThread->pServer;
  pthread_mutex_lock(&server->serverMutex);

  pContext->session = (HttpSession *)taosGetStrHashData(server->pSessionHash, pContext->user);
  if (pContext->session != NULL && pContext->session == pContext->session->signature) {
    pContext->session->access++;
    httpTrace("context:%p, fd:%d, ip:%s, user:%s, find an exist session:%p:%s:%p, access:%d, expire:%d",
              pContext, pContext->fd, pContext->ipstr, pContext->user, pContext->session, pContext->session->id,
              pContext->session->taos, pContext->session->access, pContext->session->expire);
    pContext->session->expire = (int)taosGetTimestampSec() + server->sessionExpire;
  } else {
    httpTrace("context:%p, fd:%d, ip:%s, user:%s, session not found", pContext, pContext->fd, pContext->ipstr,
              pContext->user);
  }

  pthread_mutex_unlock(&server->serverMutex);
}