#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_8__ {TYPE_1__ wpa_associate; } ;
struct viawget_wpa_param {TYPE_2__ u; } ;
struct TYPE_10__ {scalar_t__ abyCurrSSID; } ;
struct TYPE_11__ {TYPE_4__ sMgmtObj; } ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  abySSID; } ;
typedef  TYPE_3__* PWLAN_IE_SSID ;
typedef  TYPE_4__* PSMgmtObject ;
typedef  TYPE_5__* PSDevice ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_get_ssid(PSDevice pDevice,
				     struct viawget_wpa_param *param)
{
    PSMgmtObject        pMgmt = &(pDevice->sMgmtObj);
	PWLAN_IE_SSID       pItemSSID;
	int ret = 0;

    pItemSSID = (PWLAN_IE_SSID)pMgmt->abyCurrSSID;

	memcpy(param->u.wpa_associate.ssid, pItemSSID->abySSID , pItemSSID->len);
	param->u.wpa_associate.ssid_len = pItemSSID->len;

    return ret;
}