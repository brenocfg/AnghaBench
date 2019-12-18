#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_14__ {int dataLen; TYPE_1__* pSet; int /*<<< orphan*/  pTimer; TYPE_2__* pConn; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {int /*<<< orphan*/  port; int /*<<< orphan*/  handle; } ;
struct TYPE_12__ {int /*<<< orphan*/  tranId; int /*<<< orphan*/  destId; int /*<<< orphan*/  sourceId; scalar_t__ content; } ;
struct TYPE_11__ {TYPE_1__* pSet; } ;
struct TYPE_10__ {int /*<<< orphan*/  label; int /*<<< orphan*/  tmrCtrl; } ;
typedef  TYPE_1__ SUdpConnSet ;
typedef  TYPE_2__ SUdpConn ;
typedef  TYPE_3__ STaosHeader ;
typedef  TYPE_4__ SPacketInfo ;
typedef  TYPE_5__ SMonitor ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  taosProcessMonitorTimer ; 
 int /*<<< orphan*/  taosReadTcpData ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int taosReceivePacketViaTcp(uint32_t ip, STaosHeader *pHead, SUdpConn *pConn) {
  SUdpConnSet *  pSet = pConn->pSet;
  SPacketInfo *  pInfo = (SPacketInfo *)pHead->content;
  int            code = 0;
  pthread_attr_t thattr;
  pthread_t      thread;

  tTrace("%s receive packet via TCP, handle:0x%x, source:0x%08x dest:0x%08x tranId:%d", pSet->label, pInfo->handle,
         pHead->sourceId, pHead->destId, pHead->tranId);

  SMonitor *pMonitor = (SMonitor *)calloc(1, sizeof(SMonitor));
  pMonitor->dataLen = sizeof(STaosHeader) + sizeof(SPacketInfo);
  memcpy(pMonitor->data, pHead, (size_t)pMonitor->dataLen);
  pMonitor->pSet = pSet;
  pMonitor->ip = ip;
  pMonitor->port = pInfo->port;
  pMonitor->pConn = pConn;
  taosTmrReset(taosProcessMonitorTimer, 0, pMonitor, pSet->tmrCtrl, &pMonitor->pTimer);

  pthread_attr_init(&thattr);
  pthread_attr_setdetachstate(&thattr, PTHREAD_CREATE_DETACHED);
  code = pthread_create(&(thread), &thattr, taosReadTcpData, (void *)pMonitor);
  if (code < 0) {
    tTrace("%s failed to create thread to read tcp data, reason:%s", pSet->label, strerror(errno));
    pMonitor->pSet = NULL;
  }

  pthread_attr_destroy(&thattr);
  return code;
}