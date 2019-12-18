#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ status; int streamRole; int /*<<< orphan*/  vnode; } ;
typedef  TYPE_1__ SVnodeObj ;

/* Variables and functions */
 scalar_t__ TSDB_STATUS_MASTER ; 
 int /*<<< orphan*/  dTrace (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vnodeCloseStream (TYPE_1__*) ; 
 int /*<<< orphan*/  vnodeOpenStreams (TYPE_1__*,int /*<<< orphan*/ *) ; 

void vnodeUpdateStreamRole(SVnodeObj *pVnode) {
  /* SMeterObj *pObj; */

  int newRole = (pVnode->status == TSDB_STATUS_MASTER) ? 1 : 0;
  if (newRole != pVnode->streamRole) {
    dTrace("vid:%d, stream role is changed to:%d", pVnode->vnode, newRole);
    pVnode->streamRole = newRole;
    if (newRole) {
      vnodeOpenStreams(pVnode, NULL);
    } else {
      vnodeCloseStream(pVnode);
    }
  } else {
    dTrace("vid:%d, stream role is keep to:%d", pVnode->vnode, newRole);
  }
}