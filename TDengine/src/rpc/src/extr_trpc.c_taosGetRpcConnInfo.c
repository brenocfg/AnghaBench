#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {short peerPort; int chann; int sid; int /*<<< orphan*/  peerIp; int /*<<< orphan*/  peerId; } ;
typedef  TYPE_1__ SRpcConn ;

/* Variables and functions */

void taosGetRpcConnInfo(void *thandle, uint32_t *peerId, uint32_t *peerIp, short *peerPort, int *cid, int *sid) {
  SRpcConn *pConn = (SRpcConn *)thandle;

  *peerId = pConn->peerId;
  *peerIp = pConn->peerIp;
  *peerPort = pConn->peerPort;

  *cid = pConn->chann;
  *sid = pConn->sid;
}