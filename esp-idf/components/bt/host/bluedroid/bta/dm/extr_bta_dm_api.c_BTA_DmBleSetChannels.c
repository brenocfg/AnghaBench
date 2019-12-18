#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  channels; int /*<<< orphan*/ * set_channels_cb; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_BLE_SET_CHANNELS ;
typedef  int /*<<< orphan*/  tBTA_CMPL_CB ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_CHANNELS_LEN ; 
 int /*<<< orphan*/  BTA_DM_API_BLE_SET_CHANNELS_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmBleSetChannels(const uint8_t *channels, tBTA_CMPL_CB  *set_channels_cb)
{

    tBTA_DM_API_BLE_SET_CHANNELS *p_msg;

    if ((p_msg = (tBTA_DM_API_BLE_SET_CHANNELS *) osi_malloc(sizeof(tBTA_DM_API_BLE_SET_CHANNELS))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_BLE_SET_CHANNELS_EVT;

        p_msg->set_channels_cb = set_channels_cb;
        memcpy(p_msg->channels, channels, BLE_CHANNELS_LEN);

        bta_sys_sendmsg(p_msg);
    }


}