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
struct TYPE_4__ {int /*<<< orphan*/ * expireTimer; int /*<<< orphan*/  timerHandle; int /*<<< orphan*/ * pSessionHash; } ;
typedef  int /*<<< orphan*/  HttpSession ;
typedef  TYPE_1__ HttpServer ;

/* Variables and functions */
 int /*<<< orphan*/  httpError (char*) ; 
 int /*<<< orphan*/  httpProcessSessionExpire ; 
 int /*<<< orphan*/  taosHashStringStep1 ; 
 int /*<<< orphan*/ * taosInitStrHash (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

bool httpInitAllSessions(HttpServer *pServer) {
  if (pServer->pSessionHash == NULL) {
    pServer->pSessionHash = taosInitStrHash(100, sizeof(HttpSession), taosHashStringStep1);
  }
  if (pServer->pSessionHash == NULL) {
    httpError("http init session pool failed");
    return false;
  }
  if (pServer->expireTimer == NULL) {
    taosTmrReset(httpProcessSessionExpire, 50000, pServer, pServer->timerHandle, &pServer->expireTimer);
  }

  return true;
}