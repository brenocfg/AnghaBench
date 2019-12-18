#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* next; int /*<<< orphan*/  thandle; } ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; TYPE_2__* streamList; TYPE_3__* sqlList; } ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlStream ;
typedef  TYPE_3__ SSqlObj ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosStopRpcConn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_close (TYPE_1__*) ; 
 int /*<<< orphan*/  taos_close_stream (TYPE_2__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_1__*) ; 

void tscKillConnection(STscObj *pObj) {
  pthread_mutex_lock(&pObj->mutex);

  SSqlObj *pSql = pObj->sqlList;
  while (pSql) {
    taosStopRpcConn(pSql->thandle);
    pSql = pSql->next;
  }

  SSqlStream *pStream = pObj->streamList;
  while (pStream) {
    taos_close_stream(pStream);
    pStream = pStream->next;
  }

  pthread_mutex_unlock(&pObj->mutex);

  taos_close(pObj);

  tscTrace("connection:%p is killed", pObj);
}