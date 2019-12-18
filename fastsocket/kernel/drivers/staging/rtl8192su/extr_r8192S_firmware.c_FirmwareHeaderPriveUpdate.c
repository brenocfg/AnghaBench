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
struct r8192_priv {int /*<<< orphan*/  EEPROMUsbEndPointNumber; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rf_config; int /*<<< orphan*/  usb_ep_num; } ;
typedef  TYPE_1__* PRT_8192S_FIRMWARE_PRIV ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  FirmwareHeaderMapRfType (struct net_device*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

void FirmwareHeaderPriveUpdate(struct net_device *dev, PRT_8192S_FIRMWARE_PRIV 	pFwPriv)
{
	struct r8192_priv 	*priv = ieee80211_priv(dev);
	// Update USB endpoint number for RQPN settings.
	pFwPriv->usb_ep_num = priv->EEPROMUsbEndPointNumber; // endpoint number: 4, 6 and 11.
	RT_TRACE(COMP_INIT, "FirmwarePriveUpdate(): usb_ep_num(%#x)\n", pFwPriv->usb_ep_num);

	// Update RF types for RATR settings.
	pFwPriv->rf_config = FirmwareHeaderMapRfType(dev);
}