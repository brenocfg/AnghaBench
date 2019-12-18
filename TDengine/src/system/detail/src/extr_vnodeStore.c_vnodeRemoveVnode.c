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
typedef  int int32_t ;
struct TYPE_3__ {scalar_t__ maxSessions; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  dTrace (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  vnodeCalcOpenVnodes () ; 
 int vnodeCloseVnode (int) ; 
 TYPE_2__* vnodeList ; 
 int /*<<< orphan*/  vnodeRemoveDataFiles (int) ; 

int vnodeRemoveVnode(int vnode) {
  if (vnodeList == NULL) return TSDB_CODE_SUCCESS;

  if (vnodeList[vnode].cfg.maxSessions > 0) {
    int32_t ret = vnodeCloseVnode(vnode);
    if (ret != TSDB_CODE_SUCCESS) {
      return ret;
    }

    vnodeRemoveDataFiles(vnode);
  } else {
    dTrace("vid:%d, max sessions:%d, this vnode already dropped!!!", vnode, vnodeList[vnode].cfg.maxSessions);
    vnodeList[vnode].cfg.maxSessions = 0;  //reset value
    vnodeCalcOpenVnodes();
  }

  return TSDB_CODE_SUCCESS;
}