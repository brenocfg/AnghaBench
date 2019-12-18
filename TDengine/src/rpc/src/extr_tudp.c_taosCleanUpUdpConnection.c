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
struct TYPE_6__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  mutex; scalar_t__ hash; int /*<<< orphan*/  fd; int /*<<< orphan*/ * signature; } ;
struct TYPE_5__ {int server; int threads; int tcpFd; int /*<<< orphan*/  tmrCtrl; TYPE_2__* udpConn; int /*<<< orphan*/  tcpThread; } ;
typedef  TYPE_1__ SUdpConnSet ;
typedef  TYPE_2__ SUdpConn ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tTrace (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  taosCloseIpHash (scalar_t__) ; 
 int /*<<< orphan*/  taosCloseSocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosCloseTcpSocket (int) ; 
 int /*<<< orphan*/  taosTmrCleanUp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 

void taosCleanUpUdpConnection(void *handle) {
  SUdpConnSet *pSet = (SUdpConnSet *)handle;
  SUdpConn *   pConn;

  if (pSet == NULL) return;
  if (pSet->server == 1) {
    pthread_cancel(pSet->tcpThread);
  }

  for (int i = 0; i < pSet->threads; ++i) {
    pConn = pSet->udpConn + i;
    pConn->signature = NULL;
    pthread_cancel(pConn->thread);
    taosCloseSocket(pConn->fd);
    if (pConn->hash) {
      taosCloseIpHash(pConn->hash);
      pthread_mutex_destroy(&pConn->mutex);
    }
  }

  for (int i = 0; i < pSet->threads; ++i) {
    pConn = pSet->udpConn + i;
    pthread_join(pConn->thread, NULL);
    tTrace("chandle:%p is closed", pConn);
  }

  if (pSet->tcpFd >= 0) taosCloseTcpSocket(pSet->tcpFd);
  pSet->tcpFd = -1;
  taosTmrCleanUp(pSet->tmrCtrl);
  tfree(pSet);
}