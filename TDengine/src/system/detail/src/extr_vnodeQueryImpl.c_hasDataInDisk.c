#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_10__ {size_t vnode; scalar_t__ lastKeyOnFile; } ;
struct TYPE_9__ {int fileId; } ;
struct TYPE_8__ {scalar_t__ numOfFiles; int /*<<< orphan*/  cfg; int /*<<< orphan*/  fileId; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_1__ SVnodeObj ;
typedef  TYPE_2__ SQuery ;
typedef  TYPE_3__ SMeterObj ;

/* Variables and functions */
 scalar_t__ getOldestKey (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getQueryRange (TYPE_2__*,scalar_t__*,scalar_t__*) ; 
 TYPE_1__* vnodeList ; 

bool hasDataInDisk(SQuery *pQuery, SMeterObj *pMeterObj) {
  SVnodeObj *pVnode = &vnodeList[pMeterObj->vnode];
  if (pVnode->numOfFiles <= 0) {
    pQuery->fileId = -1;
    return false;
  }

  int64_t latestKey = pMeterObj->lastKeyOnFile;
  int64_t oldestKey = getOldestKey(pVnode->numOfFiles, pVnode->fileId, &pVnode->cfg);

  TSKEY min, max;
  getQueryRange(pQuery, &min, &max);

  /* query range is out of current time interval of table */
  if ((min > latestKey) || (max < oldestKey)) {
    pQuery->fileId = -1;
    return false;
  }

  return true;
}