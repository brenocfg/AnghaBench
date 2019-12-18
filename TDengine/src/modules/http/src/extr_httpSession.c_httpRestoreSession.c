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
struct TYPE_11__ {TYPE_2__* session; int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; TYPE_1__* pThread; } ;
struct TYPE_10__ {int /*<<< orphan*/  serverMutex; } ;
struct TYPE_9__ {int /*<<< orphan*/  expire; int /*<<< orphan*/  access; int /*<<< orphan*/  taos; int /*<<< orphan*/  id; struct TYPE_9__* signature; } ;
struct TYPE_8__ {TYPE_3__* pServer; } ;
typedef  TYPE_2__ HttpSession ;
typedef  TYPE_3__ HttpServer ;
typedef  TYPE_4__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  httpTrace (char*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void httpRestoreSession(HttpContext *pContext) {
  HttpServer * server = pContext->pThread->pServer;

  // all access to the session is via serverMutex
  pthread_mutex_lock(&server->serverMutex);
  HttpSession *session = pContext->session;
  if (session == NULL || session != session->signature) {
    pthread_mutex_unlock(&server->serverMutex);
    return;
  }
  session->access--;
  httpTrace("context:%p, ip:%s, user:%s, restore session:%p:%s:%p, access:%d, expire:%d",
            pContext, pContext->ipstr, pContext->user, session, session->id, session->taos,
            session->access, pContext->session->expire);
  pthread_mutex_unlock(&server->serverMutex);
}