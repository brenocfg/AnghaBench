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
struct TYPE_6__ {int /*<<< orphan*/  msgHdr; int /*<<< orphan*/ * signature; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; TYPE_1__* pConn; int /*<<< orphan*/  timer; } ;
struct TYPE_5__ {int /*<<< orphan*/  hash; } ;
typedef  TYPE_2__ SUdpBuf ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  taosDeleteIpHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosFreeMsgHdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrStopA (int /*<<< orphan*/ *) ; 

void taosRemoveUdpBuf(SUdpBuf *pBuf) {
  taosTmrStopA(&pBuf->timer);
  taosDeleteIpHash(pBuf->pConn->hash, pBuf->ip, pBuf->port);

  // tTrace("%s UDP buffer to:0x%lld:%d is removed", pBuf->pConn->label,
  // pBuf->ip, pBuf->port);

  pBuf->signature = NULL;
  taosFreeMsgHdr(pBuf->msgHdr);
  free(pBuf);
}