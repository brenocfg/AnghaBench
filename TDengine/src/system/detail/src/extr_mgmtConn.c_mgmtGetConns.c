#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int numOfConns; } ;
struct TYPE_17__ {int /*<<< orphan*/  mutex; TYPE_5__* pConn; TYPE_1__ acctInfo; } ;
struct TYPE_16__ {int /*<<< orphan*/  stime; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; int /*<<< orphan*/  user; } ;
struct TYPE_15__ {struct TYPE_15__* next; int /*<<< orphan*/  stime; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; TYPE_2__* pUser; TYPE_7__* pAcct; } ;
struct TYPE_14__ {scalar_t__ numOfConns; TYPE_6__* connInfo; scalar_t__ index; } ;
struct TYPE_13__ {TYPE_4__* pNode; } ;
struct TYPE_12__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_3__ SShowObj ;
typedef  TYPE_4__ SConnShow ;
typedef  TYPE_5__ SConnObj ;
typedef  TYPE_6__ SConnInfo ;
typedef  TYPE_7__ SAcctObj ;

/* Variables and functions */
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mgmtGetConns(SShowObj *pShow, SConnObj *pConn) {
  SAcctObj * pAcct = pConn->pAcct;
  SConnShow *pConnShow;

  pthread_mutex_lock(&pAcct->mutex);

  pConnShow = malloc(sizeof(SConnInfo) * pAcct->acctInfo.numOfConns + sizeof(SConnShow));
  pConnShow->index = 0;
  pConnShow->numOfConns = 0;

  if (pAcct->acctInfo.numOfConns > 0) {
    pConn = pAcct->pConn;
    SConnInfo *pConnInfo = pConnShow->connInfo;

    while (pConn) {
      strcpy(pConnInfo->user, pConn->pUser->user);
      pConnInfo->ip = pConn->ip;
      pConnInfo->port = pConn->port;
      pConnInfo->stime = pConn->stime;

      pConnShow->numOfConns++;
      pConnInfo++;
      pConn = pConn->next;
    }
  }

  pthread_mutex_unlock(&pAcct->mutex);

  // sorting based on useconds

  pShow->pNode = pConnShow;

  return 0;
}