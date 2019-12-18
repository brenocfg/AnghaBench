#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int replications; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; int /*<<< orphan*/  vgTimer; int /*<<< orphan*/  vgStatus; TYPE_1__ cfg; } ;
struct TYPE_15__ {int numOfVnodes; TYPE_2__* vnodeGid; int /*<<< orphan*/  vgId; int /*<<< orphan*/  createdTime; int /*<<< orphan*/  dbName; } ;
struct TYPE_14__ {int vnode; int /*<<< orphan*/  ip; } ;
typedef  TYPE_3__ SVgObj ;
typedef  TYPE_4__ SDbObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_VG_STATUS_FULL ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  mError (char*) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mgmtAllocVnodes (TYPE_3__*) ; 
 int /*<<< orphan*/  mgmtProcessVgTimer ; 
 int /*<<< orphan*/  mgmtSendVPeersMsg (TYPE_3__*) ; 
 int /*<<< orphan*/  mgmtTmr ; 
 int /*<<< orphan*/  sdbInsertRow (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosGetTimestampMs () ; 
 int /*<<< orphan*/  taosIpStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrReset (int /*<<< orphan*/ ,int,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgSdb ; 

SVgObj *mgmtCreateVgroup(SDbObj *pDb) {
  SVgObj *pVgroup;
  int     size;

  size = sizeof(SVgObj);
  pVgroup = (SVgObj *)malloc(size);
  memset(pVgroup, 0, size);
  strcpy(pVgroup->dbName, pDb->name);
  pVgroup->numOfVnodes = pDb->cfg.replications;
  pVgroup->createdTime = taosGetTimestampMs();

  // based on load balance, create a new one
  if (mgmtAllocVnodes(pVgroup) != 0) {
    mError("no enough free dnode");
    free(pVgroup);
    pDb->vgStatus = TSDB_VG_STATUS_FULL;
    taosTmrReset(mgmtProcessVgTimer, 5000, pDb, mgmtTmr, &pDb->vgTimer);
    return NULL;
  }

  sdbInsertRow(vgSdb, pVgroup, 0);

  mTrace("vgroup:%d, db:%s replica:%d is created", pVgroup->vgId, pDb->name, pVgroup->numOfVnodes);
  for (int i = 0; i < pVgroup->numOfVnodes; ++i)
    mTrace("dnode:%s, vgroup:%d, vnode:%d is created", taosIpStr(pVgroup->vnodeGid[i].ip), pVgroup->vgId, pVgroup->vnodeGid[i].vnode);

  mgmtSendVPeersMsg(pVgroup);

  return pVgroup;
}