#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SVnodeObj ;

/* Variables and functions */
 int TSDB_MAX_VNODES ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vnodeInitInfo () ; 
 scalar_t__ vnodeInitStoreVnode (int) ; 
 int /*<<< orphan*/ * vnodeList ; 

int vnodeInitStore() {
  int vnode;
  int size;

  size = sizeof(SVnodeObj) * TSDB_MAX_VNODES;
  vnodeList = (SVnodeObj *)malloc(size);
  if (vnodeList == NULL) return -1;
  memset(vnodeList, 0, size);

  if (vnodeInitInfo() < 0) return -1;

  for (vnode = 0; vnode < TSDB_MAX_VNODES; ++vnode) {
    if (vnodeInitStoreVnode(vnode) < 0) {
      // one vnode is failed to recover from commit log, continue for remain
      return -1;
    }
  }

  return 0;
}