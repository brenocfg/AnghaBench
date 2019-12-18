#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  param; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  pSql; struct TYPE_7__* next; int /*<<< orphan*/  streamId; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; TYPE_2__* streamList; } ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlStream ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_close_stream (TYPE_2__*) ; 
 int /*<<< orphan*/  tscTrace (char*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

void tscKillStream(STscObj *pObj, uint32_t killId) {
  pthread_mutex_lock(&pObj->mutex);

  SSqlStream *pStream = pObj->streamList;
  while (pStream) {
    if (pStream->streamId == killId) break;
    pStream = pStream->next;
  }

  pthread_mutex_unlock(&pObj->mutex);

  tscTrace("%p stream:%p is killed, streamId:%d", pStream->pSql, pStream, killId);

  taos_close_stream(pStream);
  if (pStream->callback) {
    pStream->callback(pStream->param);
  }
}