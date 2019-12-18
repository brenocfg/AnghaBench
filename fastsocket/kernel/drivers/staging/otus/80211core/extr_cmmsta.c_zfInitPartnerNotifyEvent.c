#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsPartnerNotifyEvent {int /*<<< orphan*/  bssid; scalar_t__ peerMacAddr; } ;
struct TYPE_3__ {scalar_t__ bssid; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ ZM_WLAN_HEADER_A2_OFFSET ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

void zfInitPartnerNotifyEvent(zdev_t* dev, zbuf_t* buf, struct zsPartnerNotifyEvent *event)
{
    u16_t  *peerMacAddr;

    zmw_get_wlan_dev(dev);

    peerMacAddr = (u16_t *)event->peerMacAddr;

    zfMemoryCopy(event->bssid, (u8_t *)(wd->sta.bssid), 6);
    peerMacAddr[0] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A2_OFFSET);
    peerMacAddr[1] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A2_OFFSET + 2);
    peerMacAddr[2] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A2_OFFSET + 4);
}