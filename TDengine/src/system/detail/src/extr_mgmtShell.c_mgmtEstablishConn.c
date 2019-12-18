#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int superAuth; int writeAuth; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; int /*<<< orphan*/  thandle; TYPE_2__* pUser; TYPE_1__* pAcct; int /*<<< orphan*/  stime; } ;
struct TYPE_7__ {int superAuth; int writeAuth; int /*<<< orphan*/  user; } ;
struct TYPE_6__ {char* user; } ;
typedef  TYPE_3__ SConnObj ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fetch_add_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mgmtAddConnIntoAcct (TYPE_3__*) ; 
 int /*<<< orphan*/  mgmtShellConns ; 
 int /*<<< orphan*/  sdbExtConns ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taosGetRpcConnInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosGetTimestampMs () ; 

void mgmtEstablishConn(SConnObj *pConn) {
  atomic_fetch_add_32(&mgmtShellConns, 1);
  atomic_fetch_add_32(&sdbExtConns, 1);
  pConn->stime = taosGetTimestampMs();

  if (strcmp(pConn->pUser->user, "root") == 0 || strcmp(pConn->pUser->user, pConn->pAcct->user) == 0) {
    pConn->superAuth = 1;
    pConn->writeAuth = 1;
  } else {
    pConn->superAuth = pConn->pUser->superAuth;
    pConn->writeAuth = pConn->pUser->writeAuth;
    if (pConn->superAuth) {
      pConn->writeAuth = 1;
    }
  }

  uint32_t temp;
  taosGetRpcConnInfo(pConn->thandle, &temp, &pConn->ip, &pConn->port, &temp, &temp);
  mgmtAddConnIntoAcct(pConn);
}