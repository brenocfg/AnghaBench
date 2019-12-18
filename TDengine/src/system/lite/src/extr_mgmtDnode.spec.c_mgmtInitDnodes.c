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
typedef  scalar_t__ uint16_t ;
typedef  int int64_t ;
struct TYPE_3__ {int createdTime; scalar_t__ numOfVnodes; void* thandle; int /*<<< orphan*/  numOfTotalVnodes; int /*<<< orphan*/  alternativeRole; int /*<<< orphan*/  status; scalar_t__ numOfCores; scalar_t__ lastReboot; int /*<<< orphan*/  privateIp; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_DNODE_ROLE_ANY ; 
 scalar_t__ TSDB_INVALID_VNODE_NUM ; 
 int /*<<< orphan*/  TSDB_STATUS_READY ; 
 TYPE_1__ dnodeObj ; 
 int /*<<< orphan*/  inet_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mPrint (char*,scalar_t__) ; 
 int /*<<< orphan*/  mgmtSetDnodeMaxVnodes (TYPE_1__*) ; 
 int /*<<< orphan*/  tsInternalIp ; 
 scalar_t__ tsNumOfCores ; 
 int /*<<< orphan*/  tsNumOfTotalVnodes ; 
 scalar_t__ tsRebootTime ; 

int mgmtInitDnodes() {
  dnodeObj.privateIp = inet_addr(tsInternalIp);;
  dnodeObj.createdTime = (int64_t)tsRebootTime * 1000;
  dnodeObj.lastReboot = tsRebootTime;
  dnodeObj.numOfCores = (uint16_t)tsNumOfCores;
  dnodeObj.status = TSDB_STATUS_READY;
  dnodeObj.alternativeRole = TSDB_DNODE_ROLE_ANY;
  dnodeObj.numOfTotalVnodes = tsNumOfTotalVnodes;
  dnodeObj.thandle = (void*)(1);  //hack way
  if (dnodeObj.numOfVnodes == TSDB_INVALID_VNODE_NUM) {
    mgmtSetDnodeMaxVnodes(&dnodeObj);
    mPrint("first access, set total vnodes:%d", dnodeObj.numOfVnodes);
  }
  return  0;
}