#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; TYPE_3__* pConn; } ;
struct TYPE_8__ {scalar_t__ ip; short port; TYPE_1__* pQList; scalar_t__ queryId; struct TYPE_8__* next; TYPE_4__* pAcct; } ;
struct TYPE_7__ {scalar_t__ queryId; } ;
struct TYPE_6__ {int numOfQueries; TYPE_2__* qdesc; } ;
typedef  TYPE_2__ SQDesc ;
typedef  TYPE_3__ SConnObj ;
typedef  TYPE_4__ SAcctObj ;

/* Variables and functions */
 int TSDB_CODE_INVALID_QUERY_ID ; 
 scalar_t__ atoi (char*) ; 
 short htons (scalar_t__) ; 
 scalar_t__ inet_addr (char*) ; 
 int /*<<< orphan*/  mTrace (char*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int mgmtKillQuery(char *qidstr, SConnObj *pConn) {
  char *temp, *chr, idstr[64];
  strcpy(idstr, qidstr);

  temp = idstr;
  chr = strchr(temp, ':');
  if (chr == NULL) goto _error;
  *chr = 0;
  uint32_t ip = inet_addr(temp);

  temp = chr + 1;
  chr = strchr(temp, ':');
  if (chr == NULL) goto _error;
  *chr = 0;
  short port = htons(atoi(temp));

  temp = chr + 1;
  uint32_t queryId = atoi(temp);

  SAcctObj *pAcct = pConn->pAcct;

  pthread_mutex_lock(&pAcct->mutex);

  pConn = pAcct->pConn;
  while (pConn) {
    if (pConn->ip == ip && pConn->port == port && pConn->pQList) {
      int     i;
      SQDesc *pQDesc = pConn->pQList->qdesc;
      for (i = 0; i < pConn->pQList->numOfQueries; ++i, ++pQDesc) {
        if (pQDesc->queryId == queryId) break;
      }

      if (i < pConn->pQList->numOfQueries) break;
    }

    pConn = pConn->next;
  }

  if (pConn) pConn->queryId = queryId;

  pthread_mutex_unlock(&pAcct->mutex);

  if (pConn == NULL || pConn->pQList == NULL || pConn->pQList->numOfQueries == 0) goto _error;

  mTrace("query:%s is there, kill it", qidstr);
  return 0;

_error:
  mTrace("query:%s is not there", qidstr);

  return TSDB_CODE_INVALID_QUERY_ID;
}