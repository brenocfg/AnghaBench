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
typedef  int int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  meterId; int /*<<< orphan*/  createFlag; } ;
typedef  int /*<<< orphan*/  STabObj ;
typedef  TYPE_1__ SMeterInfoMsg ;

/* Variables and functions */
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mgmtGetMeter (int /*<<< orphan*/ ) ; 

bool mgmtCheckMeterMetaMsgType(char *pMsg) {
  SMeterInfoMsg *pInfo = (SMeterInfoMsg *)pMsg;

  int16_t  autoCreate = htons(pInfo->createFlag);
  STabObj *pMeterObj = mgmtGetMeter(pInfo->meterId);

  // If table does not exists and autoCreate flag is set, we add the handler into another task queue, namely tranQueue
  bool addIntoTranQueue = (pMeterObj == NULL && autoCreate == 1);
  if (addIntoTranQueue) {
    mTrace("meter:%s auto created task added", pInfo->meterId);
  }

  return addIntoTranQueue;
}