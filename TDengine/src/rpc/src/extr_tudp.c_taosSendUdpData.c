#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  destAdd ;
struct TYPE_10__ {int totalLen; int /*<<< orphan*/  msgHdr; int /*<<< orphan*/  timer; } ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  fd; int /*<<< orphan*/  tmrCtrl; int /*<<< orphan*/ * hash; int /*<<< orphan*/  localPort; int /*<<< orphan*/  label; struct TYPE_9__* signature; } ;
typedef  TYPE_2__ SUdpConn ;
typedef  TYPE_3__ SUdpBuf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ RPC_MAX_UDP_PKTS ; 
 int RPC_MAX_UDP_SIZE ; 
 int /*<<< orphan*/  RPC_UDP_BUF_TIME ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sendto (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  tTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,int,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  taosAddIpHash (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,short) ; 
 TYPE_3__* taosCreateUdpBuf (TYPE_2__*,int /*<<< orphan*/ ,short) ; 
 scalar_t__ taosGetIpHash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,short) ; 
 scalar_t__ taosMsgHdrSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosProcessUdpBufTimer ; 
 int /*<<< orphan*/  taosSendMsgHdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int taosSendPacketViaTcp (int /*<<< orphan*/ ,short,char*,int,void*) ; 
 int /*<<< orphan*/  taosSetMsgHdrData (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int taosSendUdpData(uint32_t ip, short port, char *data, int dataLen, void *chandle) {
  SUdpConn *pConn = (SUdpConn *)chandle;
  SUdpBuf * pBuf;

  if (pConn == NULL || pConn->signature != pConn) return -1;

  if (dataLen >= RPC_MAX_UDP_SIZE) return taosSendPacketViaTcp(ip, port, data, dataLen, chandle);

  if (pConn->hash == NULL) {
    struct sockaddr_in destAdd;
    memset(&destAdd, 0, sizeof(destAdd));
    destAdd.sin_family = AF_INET;
    destAdd.sin_addr.s_addr = ip;
    destAdd.sin_port = htons((uint16_t)port);

    int ret = (int)sendto(pConn->fd, data, (size_t)dataLen, 0, (struct sockaddr *)&destAdd, sizeof(destAdd));
    tTrace("%s msg is sent to 0x%x:%hu len:%d ret:%d localPort:%hu chandle:0x%x", pConn->label, destAdd.sin_addr.s_addr,
           port, dataLen, ret, pConn->localPort, chandle);

    return ret;
  }

  pthread_mutex_lock(&pConn->mutex);

  pBuf = (SUdpBuf *)taosGetIpHash(pConn->hash, ip, port);
  if (pBuf == NULL) {
    pBuf = taosCreateUdpBuf(pConn, ip, port);
    taosAddIpHash(pConn->hash, pBuf, ip, port);
  }

  if ((pBuf->totalLen + dataLen > RPC_MAX_UDP_SIZE) || (taosMsgHdrSize(pBuf->msgHdr) >= RPC_MAX_UDP_PKTS)) {
    taosTmrReset(taosProcessUdpBufTimer, RPC_UDP_BUF_TIME, pBuf, pConn->tmrCtrl, &pBuf->timer);

    taosSendMsgHdr(pBuf->msgHdr, pConn->fd);
    pBuf->totalLen = 0;
  }

  taosSetMsgHdrData(pBuf->msgHdr, data, dataLen);

  pBuf->totalLen += dataLen;

  pthread_mutex_unlock(&pConn->mutex);

  return dataLen;
}