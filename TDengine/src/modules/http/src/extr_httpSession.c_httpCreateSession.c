#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* session; int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_1__* pThread; } ;
struct TYPE_11__ {int /*<<< orphan*/  serverMutex; int /*<<< orphan*/  pSessionHash; scalar_t__ sessionExpire; } ;
struct TYPE_10__ {int access; void* taos; int /*<<< orphan*/  id; struct TYPE_10__* signature; scalar_t__ expire; } ;
struct TYPE_9__ {TYPE_3__* pServer; } ;
typedef  TYPE_2__ HttpSession ;
typedef  TYPE_3__ HttpServer ;
typedef  TYPE_4__ HttpContext ;

/* Variables and functions */
 size_t HTTP_SESSION_FULL ; 
 int /*<<< orphan*/  httpError (char*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * httpMsg ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ taosAddStrHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ taosGetTimestampSec () ; 
 int /*<<< orphan*/  taos_close (void*) ; 

void httpCreateSession(HttpContext *pContext, void *taos) {
  HttpServer *server = pContext->pThread->pServer;
  pthread_mutex_lock(&server->serverMutex);

  if (pContext->session != NULL && pContext->session == pContext->session->signature) {
    httpTrace("context:%p, fd:%d, ip:%s, user:%s, set exist session:%p:%s:%p expired", pContext, pContext->fd,
              pContext->ipstr, pContext->user, pContext->session, pContext->session->id, pContext->session->taos);
    pContext->session->expire = 0;
    pContext->session->access--;
  }

  HttpSession session;
  session.taos = taos;
  session.expire = (int)taosGetTimestampSec() + server->sessionExpire;
  session.access = 1;
  strcpy(session.id, pContext->user);
  pContext->session = (HttpSession *)taosAddStrHash(server->pSessionHash, session.id, (char *)(&session));
  if (pContext->session == NULL) {
    httpError("context:%p, fd:%d, ip:%s, user:%s, error:%s", pContext, pContext->fd, pContext->ipstr, pContext->user,
              httpMsg[HTTP_SESSION_FULL]);
    taos_close(taos);
    pthread_mutex_unlock(&server->serverMutex);
    return;
  }

  pContext->session->signature = pContext->session;
  httpTrace("context:%p, fd:%d, ip:%s, user:%s, create a new session:%p:%s:%p", pContext, pContext->fd, pContext->ipstr,
            pContext->user, pContext->session, pContext->session->id, pContext->session->taos);
  pthread_mutex_unlock(&server->serverMutex);
}