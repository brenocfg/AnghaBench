#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  serverMutex; int /*<<< orphan*/  pSessionHash; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ HttpSession ;
typedef  TYPE_2__ HttpServer ;

/* Variables and functions */
 int /*<<< orphan*/  httpResetSession (char*) ; 
 int /*<<< orphan*/  httpSessionExpired ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosDeleteStrHashNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ taosVisitStrHashWithFp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void httpRemoveExpireSessions(HttpServer *pServer) {
  int expiredNum = 0;
  do {
    pthread_mutex_lock(&pServer->serverMutex);

    HttpSession *pSession = (HttpSession *)taosVisitStrHashWithFp(pServer->pSessionHash, httpSessionExpired);
    if (pSession == NULL) {
      pthread_mutex_unlock(&pServer->serverMutex);
      break;
    }

    httpResetSession((char *)pSession);
    taosDeleteStrHashNode(pServer->pSessionHash, pSession->id, pSession);

    pthread_mutex_unlock(&pServer->serverMutex);

    if (++expiredNum > 10) {
      break;
    }
  } while (true);
}