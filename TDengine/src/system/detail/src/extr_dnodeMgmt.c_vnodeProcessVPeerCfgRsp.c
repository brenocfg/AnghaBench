#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {scalar_t__ lastKey; } ;
struct TYPE_3__ {scalar_t__ code; scalar_t__ more; } ;
typedef  TYPE_1__ STaosRsp ;
typedef  int /*<<< orphan*/  SMgmtObj ;

/* Variables and functions */
 int TSDB_MAX_VNODES ; 
 int /*<<< orphan*/  dError (char*) ; 
 int /*<<< orphan*/  dTrace (char*,int) ; 
 int htonl (int /*<<< orphan*/ ) ; 
 TYPE_2__* vnodeList ; 
 int /*<<< orphan*/  vnodeProcessVPeerCfg (scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeRemoveVnode (int) ; 

int vnodeProcessVPeerCfgRsp(char *msg, int msgLen, SMgmtObj *pMgmtObj) {
  STaosRsp *pRsp;

  pRsp = (STaosRsp *)msg;

  if (pRsp->code == 0) {
    vnodeProcessVPeerCfg(pRsp->more, msgLen - sizeof(STaosRsp), pMgmtObj);
  } else {
    int32_t *pint = (int32_t *)pRsp->more;
    int      vnode = htonl(*pint);
    if (vnode < TSDB_MAX_VNODES && vnodeList[vnode].lastKey != 0) {
      dError("vnode:%d not configured, it shall be empty");
      vnodeRemoveVnode(vnode);
    } else {
      dTrace("vnode:%d is invalid", vnode);
    }
  }

  return 0;
}