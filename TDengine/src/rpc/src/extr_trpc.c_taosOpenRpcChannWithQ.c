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
typedef  int /*<<< orphan*/  pChann ;
struct TYPE_5__ {int sessions; void* qhandle; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * hash; int /*<<< orphan*/ * tmrCtrl; int /*<<< orphan*/ * idPool; int /*<<< orphan*/ * connList; } ;
struct TYPE_4__ {int numOfChanns; scalar_t__ idMgmt; void* qhandle; int /*<<< orphan*/  label; TYPE_2__* channList; } ;
typedef  TYPE_1__ STaosRpc ;
typedef  int /*<<< orphan*/  SRpcConn ;
typedef  TYPE_2__ SRpcChann ;

/* Variables and functions */
 scalar_t__ TAOS_ID_FREE ; 
 int TSDB_CODE_SUCCESS ; 
 scalar_t__ calloc (int,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tError (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  taosHashString ; 
 int /*<<< orphan*/ * taosInitIdPool (int) ; 
 int /*<<< orphan*/ * taosInitStrHash (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taosTmrInit (int,int,int,int /*<<< orphan*/ ) ; 

int taosOpenRpcChannWithQ(void *handle, int cid, int sessions, void *qhandle) {
  STaosRpc * pServer = (STaosRpc *)handle;
  SRpcChann *pChann;

  if (pServer == NULL) return -1;
  if (cid >= pServer->numOfChanns || cid < 0) {
    tError("%s: cid:%d, chann is out of range, max:%d", pServer->label, cid, pServer->numOfChanns);
    return -1;
  }

  pChann = pServer->channList + cid;
  memset(pChann, 0, sizeof(SRpcChann));

  size_t size = sizeof(SRpcConn) * sessions;
  pChann->connList = (SRpcConn *)calloc(1, size);
  if (pChann->connList == NULL) {
    tError("%s cid:%d, failed to allocate memory for taos connections, size:%d", pServer->label, cid, size);
    return -1;
  }

  if (pServer->idMgmt == TAOS_ID_FREE) {
    pChann->idPool = taosInitIdPool(sessions);
    if (pChann->idPool == NULL) {
      tError("%s cid:%d, failed to init ID pool", pServer->label, cid);
      return -1;
    }
  }

  pChann->tmrCtrl = taosTmrInit(sessions * 2 + 1, 50, 10000, pServer->label);
  if (pChann->tmrCtrl == NULL) {
    tError("%s cid:%d, failed to init timers", pServer->label, cid);
    return -1;
  }

  pChann->hash = taosInitStrHash(sessions, sizeof(pChann), taosHashString);
  if (pChann->hash == NULL) {
    tError("%s cid:%d, failed to init string hash", pServer->label, cid);
    return -1;
  }

  pthread_mutex_init(&pChann->mutex, NULL);
  pChann->sessions = sessions;

  pChann->qhandle = qhandle ? qhandle : pServer->qhandle;

  return TSDB_CODE_SUCCESS;
}