#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ sqlLen; int /*<<< orphan*/ * pStream; } ;
struct TYPE_5__ {int maxSessions; } ;
struct TYPE_6__ {int /*<<< orphan*/  numOfStreams; TYPE_3__** meterList; TYPE_1__ cfg; int /*<<< orphan*/  streamRole; int /*<<< orphan*/  vnode; } ;
typedef  TYPE_2__ SVnodeObj ;
typedef  TYPE_3__ SMeterObj ;

/* Variables and functions */
 int /*<<< orphan*/  dTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_close_stream (int /*<<< orphan*/ *) ; 

void vnodeCloseStream(SVnodeObj *pVnode) {
  SMeterObj *pObj;
  dTrace("vid:%d, stream is closed, old role:%d", pVnode->vnode, pVnode->streamRole);

  // stop stream computing
  for (int sid = 0; sid < pVnode->cfg.maxSessions; ++sid) {
    pObj = pVnode->meterList[sid];
    if (pObj == NULL) continue;
    if (pObj->sqlLen > 0 && pObj->pStream) {
      taos_close_stream(pObj->pStream);
      pVnode->numOfStreams--;
    }
    pObj->pStream = NULL;
  }
}