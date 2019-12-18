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
struct TYPE_6__ {void* signature; void* timer; int emptyNum; scalar_t__ totalLen; int /*<<< orphan*/  msgHdr; TYPE_1__* pConn; } ;
struct TYPE_5__ {int /*<<< orphan*/  tmrCtrl; int /*<<< orphan*/  mutex; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ SUdpConn ;
typedef  TYPE_2__ SUdpBuf ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_UDP_BUF_TIME ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ taosMsgHdrSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosRemoveUdpBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  taosSendMsgHdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrReset (void (*) (void*,void*),int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,void**) ; 

void taosProcessUdpBufTimer(void *param, void *tmrId) {
  SUdpBuf *pBuf = (SUdpBuf *)param;
  if (pBuf->signature != param) return;
  if (pBuf->timer != tmrId) return;

  SUdpConn *pConn = pBuf->pConn;

  pthread_mutex_lock(&pConn->mutex);

  if (taosMsgHdrSize(pBuf->msgHdr) > 0) {
    taosSendMsgHdr(pBuf->msgHdr, pConn->fd);
    pBuf->totalLen = 0;
    pBuf->emptyNum = 0;
  } else {
    pBuf->emptyNum++;
    if (pBuf->emptyNum > 200) {
      taosRemoveUdpBuf(pBuf);
      pBuf = NULL;
    }
  }

  pthread_mutex_unlock(&pConn->mutex);

  if (pBuf) taosTmrReset(taosProcessUdpBufTimer, RPC_UDP_BUF_TIME, pBuf, pConn->tmrCtrl, &pBuf->timer);
}