#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  simpleCheck ;
typedef  int /*<<< orphan*/  head ;
struct TYPE_9__ {int sid; char action; int sversion; int contLen; int simpleCheck; } ;
struct TYPE_8__ {int vnode; int sid; int sversion; } ;
struct TYPE_7__ {char* pWrite; int mappingSize; char* pMem; int mappingThreshold; int /*<<< orphan*/  logMutex; } ;
typedef  TYPE_1__ SVnodeObj ;
typedef  TYPE_2__ SMeterObj ;
typedef  TYPE_3__ SCommitHead ;

/* Variables and functions */
 int TSDB_CODE_ACTION_IN_PROGRESS ; 
 int /*<<< orphan*/  dTrace (char*,int,...) ; 
 int /*<<< orphan*/  memcpy (char*,...) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* vnodeList ; 
 int /*<<< orphan*/  vnodeProcessCommitTimer (TYPE_1__*,int /*<<< orphan*/ *) ; 

int vnodeWriteToCommitLog(SMeterObj *pObj, char action, char *cont, int contLen, int sverion) {
  SVnodeObj *pVnode = vnodeList + pObj->vnode;
  if (pVnode->pWrite == NULL) return 0;

  SCommitHead head;
  head.sid = pObj->sid;
  head.action = action;
  head.sversion = pObj->sversion;
  head.contLen = contLen;
  head.simpleCheck = (head.sversion+head.sid+head.contLen+head.action) & 0xFFFFFF;
  int simpleCheck = head.simpleCheck;

  pthread_mutex_lock(&(pVnode->logMutex));
  // 100 bytes redundant mem space
  if (pVnode->mappingSize - (pVnode->pWrite - pVnode->pMem) < contLen + sizeof(SCommitHead) + sizeof(simpleCheck) + 100) {
    pthread_mutex_unlock(&(pVnode->logMutex));
    dTrace("vid:%d, mem mapping space is not enough, wait for commit", pObj->vnode);
    vnodeProcessCommitTimer(pVnode, NULL);
    return TSDB_CODE_ACTION_IN_PROGRESS;
  }
  char *pWrite = pVnode->pWrite;
  pVnode->pWrite += sizeof(head) + contLen + sizeof(simpleCheck);
  memcpy(pWrite, (char *)&head, sizeof(head));
  memcpy(pWrite + sizeof(head), cont, contLen);
  memcpy(pWrite + sizeof(head) + contLen, &simpleCheck, sizeof(simpleCheck));
  pthread_mutex_unlock(&(pVnode->logMutex));

  if (pVnode->pWrite - pVnode->pMem > pVnode->mappingThreshold) {
    dTrace("vid:%d, mem mapping is close to limit, commit", pObj->vnode);
    vnodeProcessCommitTimer(pVnode, NULL);
  }

  dTrace("vid:%d sid:%d, data is written to commit log", pObj->vnode, pObj->sid);

  return 0;
}