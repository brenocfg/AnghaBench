#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {TYPE_2__* ptr; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
typedef  int int32_t ;
struct TYPE_10__ {scalar_t__ msgLen; } ;
struct TYPE_9__ {int numOfFds; int /*<<< orphan*/  shandle; int /*<<< orphan*/ * (* processData ) (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ;int /*<<< orphan*/  label; int /*<<< orphan*/  pollFd; int /*<<< orphan*/  mutex; int /*<<< orphan*/  fdReady; } ;
struct TYPE_8__ {int /*<<< orphan*/ * thandle; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ STcpFd ;
typedef  TYPE_3__ STcpClient ;
typedef  TYPE_4__ STaosHeader ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int epoll_wait (int /*<<< orphan*/ ,struct epoll_event*,int,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int maxTcpEvents ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 void* realloc (void*,size_t) ; 
 int /*<<< orphan*/ * stub1 (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  tError (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  tTrace (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  taosCleanUpTcpFdObj (TYPE_2__*) ; 
 int taosReadMsg (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  tfree (void*) ; 

__attribute__((used)) static void *taosReadTcpData(void *param) {
  STcpClient *       pTcp = (STcpClient *)param;
  int                i, fdNum;
  STcpFd *           pFdObj;
  struct epoll_event events[maxTcpEvents];

  while (1) {
    pthread_mutex_lock(&pTcp->mutex);
    if (pTcp->numOfFds < 1) pthread_cond_wait(&pTcp->fdReady, &pTcp->mutex);
    pthread_mutex_unlock(&pTcp->mutex);

    fdNum = epoll_wait(pTcp->pollFd, events, maxTcpEvents, -1);
    if (fdNum < 0) continue;

    for (i = 0; i < fdNum; ++i) {
      pFdObj = events[i].data.ptr;

      if (events[i].events & EPOLLERR) {
        tTrace("%s TCP error happened on FD\n", pTcp->label);
        taosCleanUpTcpFdObj(pFdObj);
        continue;
      }

      if (events[i].events & EPOLLHUP) {
        tTrace("%s TCP FD hang up\n", pTcp->label);
        taosCleanUpTcpFdObj(pFdObj);
        continue;
      }

      void *buffer = malloc(1024);
      if (NULL == buffer) {
        tTrace("%s TCP malloc(size:1024) fail\n", pTcp->label);
        taosCleanUpTcpFdObj(pFdObj);
        continue;
      }

      int headLen = taosReadMsg(pFdObj->fd, buffer, sizeof(STaosHeader));
      if (headLen != sizeof(STaosHeader)) {
        tError("%s read error, headLen:%d", pTcp->label, headLen);
        tfree(buffer);
        taosCleanUpTcpFdObj(pFdObj);
        continue;
      }

      int dataLen = (int32_t)htonl((uint32_t)((STaosHeader *)buffer)->msgLen);
      if (dataLen > 1024) {
        void *b = realloc(buffer, (size_t)dataLen);
        if (NULL == b) {
          tTrace("%s TCP malloc(size:%d) fail\n", pTcp->label, dataLen);
          tfree(buffer);
          taosCleanUpTcpFdObj(pFdObj);
          continue;
        }
        buffer = b;
      }

      int leftLen = dataLen - headLen;
      int retLen = taosReadMsg(pFdObj->fd, buffer + headLen, leftLen);

      // tTrace("%s TCP data is received, ip:%s port:%u len:%d", pTcp->label, pFdObj->ipstr, pFdObj->port, dataLen);

      if (leftLen != retLen) {
        tError("%s read error, leftLen:%d retLen:%d", pTcp->label, leftLen, retLen);
        tfree(buffer);
        taosCleanUpTcpFdObj(pFdObj);
        continue;
      }

      pFdObj->thandle =
          (*(pTcp->processData))(buffer, dataLen, pFdObj->ip, pFdObj->port, pTcp->shandle, pFdObj->thandle, pFdObj);

      if (pFdObj->thandle == NULL) taosCleanUpTcpFdObj(pFdObj);
    }
  }

  return NULL;
}