#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ vgStatus; } ;
struct TYPE_7__ {int /*<<< orphan*/  privateIp; } ;
struct TYPE_6__ {scalar_t__ code; int /*<<< orphan*/  more; } ;
typedef  TYPE_1__ STaosRsp ;
typedef  TYPE_2__ SDnodeObj ;
typedef  TYPE_3__ SDbObj ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_VG_COMMITLOG_INIT_FAILED ; 
 scalar_t__ TSDB_VG_STATUS_COMMITLOG_INIT_FAILED ; 
 scalar_t__ TSDB_VG_STATUS_INIT_FAILED ; 
 scalar_t__ TSDB_VG_STATUS_IN_PROGRESS ; 
 scalar_t__ TSDB_VG_STATUS_READY ; 
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_3__* mgmtGetDb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosIpStr (int /*<<< orphan*/ ) ; 

int mgmtProcessVPeersRsp(char *msg, int msgLen, SDnodeObj *pObj) {
  STaosRsp *pRsp = (STaosRsp *)msg;

  SDbObj *pDb = mgmtGetDb(pRsp->more);
  if (!pDb) {
    mError("dnode:%s, db not find, code:%d", taosIpStr(pObj->privateIp), pRsp->code);
    return 0;
  }

  if (pDb->vgStatus != TSDB_VG_STATUS_IN_PROGRESS) {
    mTrace("dnode:%s, db:%s vpeer rsp already disposed, code:%d", taosIpStr(pObj->privateIp), pRsp->more, pRsp->code);
    return 0;
  }

  if (pRsp->code == 0) {
    pDb->vgStatus = TSDB_VG_STATUS_READY;
    mTrace("dnode:%s, db:%s vgroup is created in dnode", taosIpStr(pObj->privateIp), pRsp->more);
    return 0;
  }

  if (pRsp->code == TSDB_CODE_VG_COMMITLOG_INIT_FAILED) {
    pDb->vgStatus = TSDB_VG_STATUS_COMMITLOG_INIT_FAILED;
  } else {
    pDb->vgStatus = TSDB_VG_STATUS_INIT_FAILED;
  }
  mError("dnode:%s, db:%s vgroup create failed, code:%d", taosIpStr(pObj->privateIp), pRsp->more, pRsp->code);

  return 0;
}