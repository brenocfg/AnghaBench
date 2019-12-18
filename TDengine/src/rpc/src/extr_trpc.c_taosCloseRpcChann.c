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
struct TYPE_7__ {int /*<<< orphan*/ * signature; } ;
struct TYPE_6__ {int sessions; int /*<<< orphan*/  mutex; TYPE_3__* connList; int /*<<< orphan*/  idPool; int /*<<< orphan*/  tmrCtrl; int /*<<< orphan*/  hash; } ;
struct TYPE_5__ {int numOfChanns; TYPE_2__* channList; int /*<<< orphan*/  label; } ;
typedef  TYPE_1__ STaosRpc ;
typedef  TYPE_2__ SRpcChann ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tError (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  taosCleanUpStrHash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosCloseRpcConn (void*) ; 
 int /*<<< orphan*/  taosIdPoolCleanUp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrCleanUp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (TYPE_3__*) ; 

void taosCloseRpcChann(void *handle, int cid) {
  STaosRpc * pServer = (STaosRpc *)handle;
  SRpcChann *pChann;

  if (pServer == NULL) return;
  if (cid >= pServer->numOfChanns || cid < 0) {
    tError("%s cid:%d, chann is out of range, max:%d", pServer->label, cid, pServer->numOfChanns);
    return;
  }

  pChann = pServer->channList + cid;

  for (int i = 0; i < pChann->sessions; ++i) {
    if (pChann->connList[i].signature != NULL) {
      taosCloseRpcConn((void *)(pChann->connList + i));
    }
  }

  taosCleanUpStrHash(pChann->hash);
  taosTmrCleanUp(pChann->tmrCtrl);
  taosIdPoolCleanUp(pChann->idPool);
  tfree(pChann->connList);
  pthread_mutex_destroy(&pChann->mutex);

  memset(pChann, 0, sizeof(SRpcChann));
}