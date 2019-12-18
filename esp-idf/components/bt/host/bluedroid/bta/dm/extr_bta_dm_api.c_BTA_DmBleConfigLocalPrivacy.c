#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_SET_LOCAL_PRIVACY_CBACK ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_6__ {int /*<<< orphan*/ * set_local_privacy_cback; int /*<<< orphan*/  privacy_enable; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_LOCAL_PRIVACY ;
typedef  int /*<<< orphan*/  tBTA_DM_API_ENABLE_PRIVACY ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_LOCAL_PRIVACY_EVT ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmBleConfigLocalPrivacy(BOOLEAN privacy_enable, tBTA_SET_LOCAL_PRIVACY_CBACK *set_local_privacy_cback)
{
    ///This function used the irk to generate the resolve address
#if BLE_INCLUDED == TRUE && BLE_PRIVACY_SPT == TRUE
    tBTA_DM_API_LOCAL_PRIVACY *p_msg;

    if ((p_msg = (tBTA_DM_API_LOCAL_PRIVACY *) osi_malloc(sizeof(tBTA_DM_API_ENABLE_PRIVACY))) != NULL) {
        memset (p_msg, 0, sizeof(tBTA_DM_API_LOCAL_PRIVACY));

        p_msg->hdr.event = BTA_DM_API_LOCAL_PRIVACY_EVT;
        p_msg->privacy_enable   = privacy_enable;
        p_msg->set_local_privacy_cback = set_local_privacy_cback;
        bta_sys_sendmsg(p_msg);
    }
#else
    UNUSED (privacy_enable);
#endif
}