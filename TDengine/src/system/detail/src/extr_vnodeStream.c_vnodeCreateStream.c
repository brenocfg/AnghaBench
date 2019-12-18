#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ sqlLen; int vnode; scalar_t__ pStream; int /*<<< orphan*/  lastKey; int /*<<< orphan*/  pSql; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; } ;
struct TYPE_7__ {scalar_t__ streamRole; int /*<<< orphan*/  numOfStreams; int /*<<< orphan*/ * dbConn; int /*<<< orphan*/ * streamTimer; } ;
typedef  TYPE_1__ SVnodeObj ;
typedef  TYPE_2__ SMeterObj ;

/* Variables and functions */
 int /*<<< orphan*/  dTrace (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ taos_open_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeCloseStreamCallback ; 
 TYPE_1__* vnodeList ; 
 int /*<<< orphan*/  vnodeOpenStreams ; 
 int /*<<< orphan*/  vnodeProcessStreamRes ; 
 int /*<<< orphan*/  vnodeTmrCtrl ; 

void vnodeCreateStream(SMeterObj *pObj) {
  if (pObj->sqlLen <= 0) return;

  SVnodeObj *pVnode = vnodeList + pObj->vnode;

  if (pVnode->streamRole == 0) return;
  if (pObj->pStream) return;

  dTrace("vid:%d sid:%d id:%s stream:%s is created", pObj->vnode, pObj->sid, pObj->meterId, pObj->pSql);
  if (pVnode->dbConn == NULL) {
    if (pVnode->streamTimer == NULL) taosTmrReset(vnodeOpenStreams, 1000, pVnode, vnodeTmrCtrl, &pVnode->streamTimer);
  } else {
    pObj->pStream = taos_open_stream(pVnode->dbConn, pObj->pSql, vnodeProcessStreamRes, pObj->lastKey, pObj,
                                     vnodeCloseStreamCallback);
    if (pObj->pStream) pVnode->numOfStreams++;
  }
}