#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; TYPE_1__* pConn; } ;
struct TYPE_4__ {scalar_t__ ip; short port; int killConnection; struct TYPE_4__* next; TYPE_2__* pAcct; } ;
typedef  TYPE_1__ SConnObj ;
typedef  TYPE_2__ SAcctObj ;

/* Variables and functions */
 int TSDB_CODE_INVALID_CONNECTION ; 
 int /*<<< orphan*/  atoi (char*) ; 
 short htons (int /*<<< orphan*/ ) ; 
 scalar_t__ inet_addr (char*) ; 
 int /*<<< orphan*/  mTrace (char*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int mgmtKillConnection(char *qidstr, SConnObj *pConn) {
  SConnObj *pConn1 = NULL;
  char *    temp, *chr, idstr[64];
  strcpy(idstr, qidstr);

  temp = idstr;
  chr = strchr(temp, ':');
  if (chr == NULL) goto _error;
  *chr = 0;
  uint32_t ip = inet_addr(temp);

  temp = chr + 1;
  short port = htons(atoi(temp));

  SAcctObj *pAcct = pConn->pAcct;

  pthread_mutex_lock(&pAcct->mutex);

  pConn = pAcct->pConn;
  while (pConn) {
    if (pConn->ip == ip && pConn->port == port) {
      // there maybe two connections from a shell
      if (pConn1 == NULL)
        pConn1 = pConn;
      else
        break;
    }

    pConn = pConn->next;
  }

  if (pConn1) pConn1->killConnection = 1;
  if (pConn) pConn->killConnection = 1;

  pthread_mutex_unlock(&pAcct->mutex);

  if (pConn1 == NULL) goto _error;

  mTrace("connection:%s is there, kill it", qidstr);
  return 0;

_error:
  mTrace("connection:%s is not there", qidstr);

  return TSDB_CODE_INVALID_CONNECTION;
}