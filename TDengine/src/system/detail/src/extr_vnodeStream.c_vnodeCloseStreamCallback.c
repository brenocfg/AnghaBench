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
struct TYPE_6__ {scalar_t__ sqlLen; int vnode; int /*<<< orphan*/ * pStream; int /*<<< orphan*/ * pSql; } ;
struct TYPE_5__ {scalar_t__ numOfStreams; int /*<<< orphan*/ * dbConn; } ;
typedef  TYPE_1__ SVnodeObj ;
typedef  TYPE_2__ SMeterObj ;

/* Variables and functions */
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 
 TYPE_1__* vnodeList ; 
 int /*<<< orphan*/  vnodeSaveMeterObjToFile (TYPE_2__*) ; 

void vnodeCloseStreamCallback(void *param) {
  SMeterObj *pMeter = (SMeterObj *)param;
  SVnodeObj *pVnode = NULL;

  if (pMeter == NULL || pMeter->sqlLen == 0) return;
  pVnode = vnodeList + pMeter->vnode;

  pMeter->sqlLen = 0;
  pMeter->pSql = NULL;
  pMeter->pStream = NULL;

  pVnode->numOfStreams--;

  if (pVnode->numOfStreams == 0) {
    taos_close(pVnode->dbConn);
    pVnode->dbConn = NULL;
  }

  vnodeSaveMeterObjToFile(pMeter);
}