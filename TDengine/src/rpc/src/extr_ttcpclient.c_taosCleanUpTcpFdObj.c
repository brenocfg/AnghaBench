#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ numOfFds; int /*<<< orphan*/  label; int /*<<< orphan*/  shandle; int /*<<< orphan*/  (* processData ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ;int /*<<< orphan*/  mutex; TYPE_1__* pHead; int /*<<< orphan*/  pollFd; } ;
struct TYPE_10__ {scalar_t__ thandle; TYPE_2__* prev; TYPE_1__* next; int /*<<< orphan*/  fd; TYPE_4__* pTcp; struct TYPE_10__* signature; } ;
struct TYPE_9__ {TYPE_1__* next; } ;
struct TYPE_8__ {TYPE_2__* prev; } ;
typedef  TYPE_3__ STcpFd ;
typedef  TYPE_4__ STcpClient ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tError (char*,...) ; 
 int /*<<< orphan*/  tTrace (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tfree (TYPE_3__*) ; 

__attribute__((used)) static void taosCleanUpTcpFdObj(STcpFd *pFdObj) {
  STcpClient *pTcp;

  if (pFdObj == NULL) return;
  if (pFdObj->signature != pFdObj) return;

  pTcp = pFdObj->pTcp;
  if (pTcp == NULL) {
    tError("double free TcpFdObj!!!!");
    return;
  }

  epoll_ctl(pTcp->pollFd, EPOLL_CTL_DEL, pFdObj->fd, NULL);
  close(pFdObj->fd);

  pthread_mutex_lock(&pTcp->mutex);

  pTcp->numOfFds--;

  if (pTcp->numOfFds < 0) tError("%s number of TCP FDs shall never be negative", pTcp->label);

  // remove from the FdObject list

  if (pFdObj->prev) {
    (pFdObj->prev)->next = pFdObj->next;
  } else {
    pTcp->pHead = pFdObj->next;
  }

  if (pFdObj->next) {
    (pFdObj->next)->prev = pFdObj->prev;
  }

  pthread_mutex_unlock(&pTcp->mutex);

  // notify the upper layer to clean the associated context
  if (pFdObj->thandle) (*(pTcp->processData))(NULL, 0, 0, 0, pTcp->shandle, pFdObj->thandle, NULL);

  tTrace("%s TCP FD is cleaned up, numOfFds:%d", pTcp->label, pTcp->numOfFds);

  memset(pFdObj, 0, sizeof(STcpFd));

  tfree(pFdObj);
}