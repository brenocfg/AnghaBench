#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int numOfQueries; int numOfConns; } ;
struct TYPE_19__ {int /*<<< orphan*/  mutex; TYPE_6__* pConn; TYPE_1__ acctInfo; } ;
struct TYPE_18__ {int /*<<< orphan*/  user; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
struct TYPE_17__ {struct TYPE_17__* next; TYPE_3__* pQList; TYPE_2__* pUser; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; TYPE_8__* pAcct; } ;
struct TYPE_16__ {scalar_t__ numOfQueries; TYPE_7__** cdesc; TYPE_7__* connInfo; int /*<<< orphan*/ * qdesc; scalar_t__ index; } ;
struct TYPE_15__ {TYPE_5__* pNode; } ;
struct TYPE_14__ {int numOfQueries; int /*<<< orphan*/  qdesc; } ;
struct TYPE_13__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_4__ SShowObj ;
typedef  TYPE_5__ SQueryShow ;
typedef  int /*<<< orphan*/  SQDesc ;
typedef  TYPE_6__ SConnObj ;
typedef  TYPE_7__ SCDesc ;
typedef  TYPE_8__ SAcctObj ;

/* Variables and functions */
 TYPE_5__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mgmtGetQueries(SShowObj *pShow, SConnObj *pConn) {
  SAcctObj *  pAcct = pConn->pAcct;
  SQueryShow *pQueryShow;

  pthread_mutex_lock(&pAcct->mutex);

  pQueryShow = malloc(sizeof(SQDesc) * pAcct->acctInfo.numOfQueries + sizeof(SQueryShow));
  pQueryShow->numOfQueries = 0;
  pQueryShow->index = 0;
  pQueryShow->connInfo = NULL;
  pQueryShow->cdesc = NULL;

  if (pAcct->acctInfo.numOfQueries > 0) {
    pQueryShow->connInfo = (SCDesc *)malloc(pAcct->acctInfo.numOfConns * sizeof(SCDesc));
    pQueryShow->cdesc = (SCDesc **)malloc(pAcct->acctInfo.numOfQueries * sizeof(SCDesc *));

    pConn = pAcct->pConn;
    SQDesc * pQdesc = pQueryShow->qdesc;
    SCDesc * pCDesc = pQueryShow->connInfo;
    SCDesc **ppCDesc = pQueryShow->cdesc;

    while (pConn) {
      if (pConn->pQList && pConn->pQList->numOfQueries > 0) {
        pCDesc->ip = pConn->ip;
        pCDesc->port = pConn->port;
        strcpy(pCDesc->user, pConn->pUser->user);

        memcpy(pQdesc, pConn->pQList->qdesc, sizeof(SQDesc) * pConn->pQList->numOfQueries);
        pQdesc += pConn->pQList->numOfQueries;
        pQueryShow->numOfQueries += pConn->pQList->numOfQueries;
        for (int i = 0; i < pConn->pQList->numOfQueries; ++i, ++ppCDesc) *ppCDesc = pCDesc;

        pCDesc++;
      }
      pConn = pConn->next;
    }
  }

  pthread_mutex_unlock(&pAcct->mutex);

  // sorting based on useconds

  pShow->pNode = pQueryShow;

  return 0;
}