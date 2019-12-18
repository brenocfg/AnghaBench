#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct usb_hub_descriptor {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  b_hnp_enable; int /*<<< orphan*/  otg_port; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct ohci_hcd {int num_ports; TYPE_3__* regs; int /*<<< orphan*/  (* start_hnp ) (struct ohci_hcd*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * portstatus; int /*<<< orphan*/  status; } ;
struct TYPE_6__ {TYPE_2__ roothub; } ;

/* Variables and functions */
#define  C_HUB_LOCAL_POWER 145 
#define  C_HUB_OVER_CURRENT 144 
#define  ClearHubFeature 143 
#define  ClearPortFeature 142 
 int EPIPE ; 
 int ESHUTDOWN ; 
#define  GetHubDescriptor 141 
#define  GetHubStatus 140 
#define  GetPortStatus 139 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 int RH_HS_CRWE ; 
 int RH_HS_DRWE ; 
 int RH_HS_OCIC ; 
 int RH_PS_CCS ; 
 int RH_PS_CSC ; 
 int RH_PS_LSDA ; 
 int RH_PS_OCIC ; 
 int RH_PS_PESC ; 
 int RH_PS_POCI ; 
 int RH_PS_PPS ; 
 int RH_PS_PRSC ; 
 int RH_PS_PSS ; 
 int RH_PS_PSSC ; 
#define  SetHubFeature 138 
#define  SetPortFeature 137 
#define  USB_PORT_FEAT_C_CONNECTION 136 
#define  USB_PORT_FEAT_C_ENABLE 135 
#define  USB_PORT_FEAT_C_OVER_CURRENT 134 
#define  USB_PORT_FEAT_C_RESET 133 
#define  USB_PORT_FEAT_C_SUSPEND 132 
#define  USB_PORT_FEAT_ENABLE 131 
#define  USB_PORT_FEAT_POWER 130 
#define  USB_PORT_FEAT_RESET 129 
#define  USB_PORT_FEAT_SUSPEND 128 
 int /*<<< orphan*/  dbg_port (struct ohci_hcd*,char*,int,int) ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_hub_descriptor (struct ohci_hcd*,struct usb_hub_descriptor*) ; 
 int /*<<< orphan*/  ohci_writel (struct ohci_hcd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,char*) ; 
 int root_port_reset (struct ohci_hcd*,int) ; 
 int roothub_portstatus (struct ohci_hcd*,int) ; 
 int roothub_status (struct ohci_hcd*) ; 
 int /*<<< orphan*/  stub1 (struct ohci_hcd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ohci_hub_control (
	struct usb_hcd	*hcd,
	u16		typeReq,
	u16		wValue,
	u16		wIndex,
	char		*buf,
	u16		wLength
) {
	struct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	int		ports = ohci->num_ports;
	u32		temp;
	int		retval = 0;

	if (unlikely(!HCD_HW_ACCESSIBLE(hcd)))
		return -ESHUTDOWN;

	switch (typeReq) {
	case ClearHubFeature:
		switch (wValue) {
		case C_HUB_OVER_CURRENT:
			ohci_writel (ohci, RH_HS_OCIC,
					&ohci->regs->roothub.status);
		case C_HUB_LOCAL_POWER:
			break;
		default:
			goto error;
		}
		break;
	case ClearPortFeature:
		if (!wIndex || wIndex > ports)
			goto error;
		wIndex--;

		switch (wValue) {
		case USB_PORT_FEAT_ENABLE:
			temp = RH_PS_CCS;
			break;
		case USB_PORT_FEAT_C_ENABLE:
			temp = RH_PS_PESC;
			break;
		case USB_PORT_FEAT_SUSPEND:
			temp = RH_PS_POCI;
			break;
		case USB_PORT_FEAT_C_SUSPEND:
			temp = RH_PS_PSSC;
			break;
		case USB_PORT_FEAT_POWER:
			temp = RH_PS_LSDA;
			break;
		case USB_PORT_FEAT_C_CONNECTION:
			temp = RH_PS_CSC;
			break;
		case USB_PORT_FEAT_C_OVER_CURRENT:
			temp = RH_PS_OCIC;
			break;
		case USB_PORT_FEAT_C_RESET:
			temp = RH_PS_PRSC;
			break;
		default:
			goto error;
		}
		ohci_writel (ohci, temp,
				&ohci->regs->roothub.portstatus [wIndex]);
		// ohci_readl (ohci, &ohci->regs->roothub.portstatus [wIndex]);
		break;
	case GetHubDescriptor:
		ohci_hub_descriptor (ohci, (struct usb_hub_descriptor *) buf);
		break;
	case GetHubStatus:
		temp = roothub_status (ohci) & ~(RH_HS_CRWE | RH_HS_DRWE);
		put_unaligned_le32(temp, buf);
		break;
	case GetPortStatus:
		if (!wIndex || wIndex > ports)
			goto error;
		wIndex--;
		temp = roothub_portstatus (ohci, wIndex);
		put_unaligned_le32(temp, buf);

#ifndef	OHCI_VERBOSE_DEBUG
	if (*(u16*)(buf+2))	/* only if wPortChange is interesting */
#endif
		dbg_port (ohci, "GetStatus", wIndex, temp);
		break;
	case SetHubFeature:
		switch (wValue) {
		case C_HUB_OVER_CURRENT:
			// FIXME:  this can be cleared, yes?
		case C_HUB_LOCAL_POWER:
			break;
		default:
			goto error;
		}
		break;
	case SetPortFeature:
		if (!wIndex || wIndex > ports)
			goto error;
		wIndex--;
		switch (wValue) {
		case USB_PORT_FEAT_SUSPEND:
#ifdef	CONFIG_USB_OTG
			if (hcd->self.otg_port == (wIndex + 1)
					&& hcd->self.b_hnp_enable)
				ohci->start_hnp(ohci);
			else
#endif
			ohci_writel (ohci, RH_PS_PSS,
				&ohci->regs->roothub.portstatus [wIndex]);
			break;
		case USB_PORT_FEAT_POWER:
			ohci_writel (ohci, RH_PS_PPS,
				&ohci->regs->roothub.portstatus [wIndex]);
			break;
		case USB_PORT_FEAT_RESET:
			retval = root_port_reset (ohci, wIndex);
			break;
		default:
			goto error;
		}
		break;

	default:
error:
		/* "protocol stall" on error */
		retval = -EPIPE;
	}
	return retval;
}