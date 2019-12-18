#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_7__ {TYPE_1__ wpa_associate; } ;
struct viawget_wpa_param {TYPE_2__ u; } ;
struct TYPE_9__ {TYPE_3__* pMgmt; } ;
struct TYPE_8__ {int /*<<< orphan*/  abyCurrBSSID; } ;
typedef  TYPE_3__* PSMgmtObject ;
typedef  TYPE_4__* PSDevice ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wpa_get_bssid(PSDevice pDevice,
				     struct viawget_wpa_param *param)
{
    PSMgmtObject        pMgmt = pDevice->pMgmt;
	int ret = 0;

	memcpy(param->u.wpa_associate.bssid, pMgmt->abyCurrBSSID , 6);

    return ret;

}