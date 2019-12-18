#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct xhci_hcd {int /*<<< orphan*/  hcc_params; } ;
struct usb_hub_descriptor {int bPwrOn2PwrGood; int bNbrPorts; int /*<<< orphan*/  wHubCharacteristics; scalar_t__ bHubContrCurrent; } ;

/* Variables and functions */
 scalar_t__ HCC_PPC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUB_CHAR_INDV_PORT_LPSM ; 
 int /*<<< orphan*/  HUB_CHAR_INDV_PORT_OCPM ; 
 int /*<<< orphan*/  HUB_CHAR_NO_LPSM ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xhci_common_hub_descriptor(struct xhci_hcd *xhci,
		struct usb_hub_descriptor *desc, int ports)
{
	u16 temp;

	desc->bPwrOn2PwrGood = 10;	/* xhci section 5.4.9 says 20ms max */
	desc->bHubContrCurrent = 0;

	desc->bNbrPorts = ports;
	temp = 0;
	/* Bits 1:0 - support per-port power switching, or power always on */
	if (HCC_PPC(xhci->hcc_params))
		temp |= HUB_CHAR_INDV_PORT_LPSM;
	else
		temp |= HUB_CHAR_NO_LPSM;
	/* Bit  2 - root hubs are not part of a compound device */
	/* Bits 4:3 - individual port over current protection */
	temp |= HUB_CHAR_INDV_PORT_OCPM;
	/* Bits 6:5 - no TTs in root ports */
	/* Bit  7 - no port indicators */
	desc->wHubCharacteristics = cpu_to_le16(temp);
}