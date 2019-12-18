#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  expireTimer; int /*<<< orphan*/  timerHandle; } ;
typedef  TYPE_1__ HttpServer ;

/* Variables and functions */
 int /*<<< orphan*/  httpRemoveExpireSessions (TYPE_1__*) ; 
 int /*<<< orphan*/  taosTmrReset (void (*) (void*,void*),int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void httpProcessSessionExpire(void *handle, void *tmrId) {
  HttpServer *pServer = (HttpServer *)handle;
  httpRemoveExpireSessions(pServer);
  taosTmrReset(httpProcessSessionExpire, 60000, pServer, pServer->timerHandle, &pServer->expireTimer);
}