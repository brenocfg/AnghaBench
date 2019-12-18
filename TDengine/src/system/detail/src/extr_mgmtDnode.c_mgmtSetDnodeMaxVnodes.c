#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numOfCores; int numOfTotalVnodes; scalar_t__ alternativeRole; int numOfVnodes; int numOfFreeVnodes; int /*<<< orphan*/  status; scalar_t__ openVnodes; } ;
typedef  TYPE_1__ SDnodeObj ;

/* Variables and functions */
 scalar_t__ TSDB_DNODE_ROLE_MGMT ; 
 int TSDB_MAX_VNODES ; 
 int TSDB_MIN_VNODES ; 
 int /*<<< orphan*/  TSDB_STATUS_OFFLINE ; 
 int /*<<< orphan*/  TSDB_STATUS_READY ; 
 int tsNumOfVnodesPerCore ; 

void mgmtSetDnodeMaxVnodes(SDnodeObj *pDnode) {
  int maxVnodes = pDnode->numOfCores * tsNumOfVnodesPerCore;
  maxVnodes = maxVnodes > TSDB_MAX_VNODES ? TSDB_MAX_VNODES : maxVnodes;
  maxVnodes = maxVnodes < TSDB_MIN_VNODES ? TSDB_MIN_VNODES : maxVnodes;
  if (pDnode->numOfTotalVnodes != 0) {
    maxVnodes = pDnode->numOfTotalVnodes;
  }
  if (pDnode->alternativeRole == TSDB_DNODE_ROLE_MGMT) {
    maxVnodes = 0;
  }

  pDnode->numOfVnodes = maxVnodes;
  pDnode->numOfFreeVnodes = maxVnodes;
  pDnode->openVnodes = 0;

#ifdef CLUSTER
  pDnode->status = TSDB_STATUS_OFFLINE;
#else
  pDnode->status = TSDB_STATUS_READY;
#endif
}