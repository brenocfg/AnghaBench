#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int inactive_sec; } ;
struct TYPE_9__ {TYPE_1__ get_info_sta; } ;
struct viawget_hostapd_param {TYPE_2__ u; int /*<<< orphan*/  sta_addr; } ;
typedef  size_t UINT ;
struct TYPE_11__ {TYPE_3__* sNodeDBTable; } ;
struct TYPE_12__ {TYPE_4__ sMgmtObj; } ;
struct TYPE_10__ {int ulLastRxJiffer; } ;
typedef  TYPE_4__* PSMgmtObject ;
typedef  TYPE_5__* PSDevice ;

/* Variables and functions */
 scalar_t__ BSSbIsSTAInNodeDB (TYPE_5__*,int /*<<< orphan*/ ,size_t*) ; 
 int ENOENT ; 
 int HZ ; 
 int jiffies ; 

__attribute__((used)) static int hostap_get_info_sta(PSDevice pDevice,
				       struct viawget_hostapd_param *param)
{
    PSMgmtObject    pMgmt = &(pDevice->sMgmtObj);
	UINT uNodeIndex;

    if (BSSbIsSTAInNodeDB(pDevice, param->sta_addr, &uNodeIndex)) {
	    param->u.get_info_sta.inactive_sec =
	        (jiffies - pMgmt->sNodeDBTable[uNodeIndex].ulLastRxJiffer) / HZ;

	    //param->u.get_info_sta.txexc = pMgmt->sNodeDBTable[uNodeIndex].uTxAttempts;
	}
	else {
	    return -ENOENT;
	}

	return 0;
}