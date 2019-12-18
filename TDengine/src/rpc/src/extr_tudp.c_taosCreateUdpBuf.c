#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_9__ {void* s_addr; } ;
struct TYPE_12__ {scalar_t__ sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_11__ {short port; int /*<<< orphan*/  timer; struct TYPE_11__* signature; TYPE_5__ destAdd; int /*<<< orphan*/  msgHdr; TYPE_2__* pConn; void* ip; } ;
struct TYPE_10__ {int /*<<< orphan*/  tmrCtrl; } ;
typedef  TYPE_2__ SUdpConn ;
typedef  TYPE_3__ SUdpBuf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  RPC_MAX_UDP_PKTS ; 
 int /*<<< orphan*/  RPC_UDP_BUF_TIME ; 
 scalar_t__ htons (scalar_t__) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taosInitMsgHdr (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosProcessUdpBufTimer ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

SUdpBuf *taosCreateUdpBuf(SUdpConn *pConn, uint32_t ip, short port) {
  SUdpBuf *pBuf = (SUdpBuf *)malloc(sizeof(SUdpBuf));
  memset(pBuf, 0, sizeof(SUdpBuf));

  pBuf->ip = ip;
  pBuf->port = port;
  pBuf->pConn = pConn;

  pBuf->destAdd.sin_family = AF_INET;
  pBuf->destAdd.sin_addr.s_addr = ip;
  pBuf->destAdd.sin_port = (uint16_t)htons((uint16_t)port);
  taosInitMsgHdr(&(pBuf->msgHdr), &(pBuf->destAdd), RPC_MAX_UDP_PKTS);
  pBuf->signature = pBuf;
  taosTmrReset(taosProcessUdpBufTimer, RPC_UDP_BUF_TIME, pBuf, pConn->tmrCtrl, &pBuf->timer);

  // tTrace("%s UDP buffer to:0x%lld:%d is created", pBuf->pConn->label,
  // pBuf->ip, pBuf->port);

  return pBuf;
}