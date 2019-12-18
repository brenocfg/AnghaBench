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
struct TYPE_7__ {int /*<<< orphan*/ ** meterList; } ;
struct TYPE_6__ {size_t vnode; size_t sid; int /*<<< orphan*/  meterId; } ;
typedef  TYPE_1__ SMeterObj ;

/* Variables and functions */
 int /*<<< orphan*/  dTrace (char*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tListLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 
 int /*<<< orphan*/  vnodeFreeCacheInfo (TYPE_1__*) ; 
 TYPE_2__* vnodeList ; 

void vnodeFreeMeterObj(SMeterObj *pObj) {
  if (pObj == NULL) return;

  dTrace("vid:%d sid:%d id:%s, meter is cleaned up", pObj->vnode, pObj->sid, pObj->meterId);

  vnodeFreeCacheInfo(pObj);
  if (vnodeList[pObj->vnode].meterList != NULL) {
    vnodeList[pObj->vnode].meterList[pObj->sid] = NULL;
  }

  memset(pObj->meterId, 0, tListLen(pObj->meterId));
  tfree(pObj);
}