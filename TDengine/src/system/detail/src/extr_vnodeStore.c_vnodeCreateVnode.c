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
struct TYPE_2__ {int /*<<< orphan*/  cfg; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  SVnodeCfg ;
typedef  int /*<<< orphan*/  SVPeerDesc ;

/* Variables and functions */
 int TSDB_CODE_VG_COMMITLOG_INIT_FAILED ; 
 int TSDB_CODE_VG_INIT_FAILED ; 
 int /*<<< orphan*/  TSDB_STATUS_CREATING ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 char* tsDirectory ; 
 scalar_t__ vnodeCreateMeterObjFile (int) ; 
 scalar_t__ vnodeInitStoreVnode (int) ; 
 TYPE_1__* vnodeList ; 
 int vnodeOpenVnode (int) ; 
 scalar_t__ vnodeSaveVnodeCfg (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int vnodeCreateVnode(int vnode, SVnodeCfg *pCfg, SVPeerDesc *pDesc) {
  char fileName[128];

  vnodeList[vnode].status = TSDB_STATUS_CREATING;

  sprintf(fileName, "%s/vnode%d", tsDirectory, vnode);
  mkdir(fileName, 0755);

  sprintf(fileName, "%s/vnode%d/db", tsDirectory, vnode);
  mkdir(fileName, 0755);

  vnodeList[vnode].cfg = *pCfg;
  if (vnodeCreateMeterObjFile(vnode) != 0) {
    return TSDB_CODE_VG_INIT_FAILED;
  }

  if (vnodeSaveVnodeCfg(vnode, pCfg, pDesc) != 0) {
    return TSDB_CODE_VG_INIT_FAILED;
  }

  if (vnodeInitStoreVnode(vnode) != 0) {
    return TSDB_CODE_VG_COMMITLOG_INIT_FAILED;
  }

  return vnodeOpenVnode(vnode);
}