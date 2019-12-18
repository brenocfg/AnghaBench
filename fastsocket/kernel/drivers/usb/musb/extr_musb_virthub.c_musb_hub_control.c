#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {int* DeviceRemovable; } ;
struct TYPE_6__ {TYPE_1__ hs; } ;
struct usb_hub_descriptor {int bDescLength; int bDescriptorType; int bNbrPorts; int bPwrOn2PwrGood; TYPE_2__ u; int /*<<< orphan*/  bHubContrCurrent; int /*<<< orphan*/  wHubCharacteristics; } ;
struct TYPE_8__ {int /*<<< orphan*/  is_b_host; } ;
struct usb_hcd {TYPE_4__ self; } ;
struct musb {int port1_status; int is_active; int /*<<< orphan*/  lock; int /*<<< orphan*/  mregs; TYPE_3__* xceiv; int /*<<< orphan*/  rh_timer; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
#define  C_HUB_LOCAL_POWER 146 
#define  C_HUB_OVER_CURRENT 145 
#define  ClearHubFeature 144 
#define  ClearPortFeature 143 
 int /*<<< orphan*/  DBG (int,char*,int) ; 
 int EPIPE ; 
 int ESHUTDOWN ; 
#define  GetHubDescriptor 142 
#define  GetHubStatus 141 
#define  GetPortStatus 140 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 int /*<<< orphan*/  MUSB_DEVCTL ; 
 int MUSB_DEVCTL_SESSION ; 
 int MUSB_PORT_STAT_RESUME ; 
 int /*<<< orphan*/  MUSB_POWER ; 
 int MUSB_POWER_RESUME ; 
 int /*<<< orphan*/  MUSB_TESTMODE ; 
 int MUSB_TEST_FIFO_ACCESS ; 
 int MUSB_TEST_FORCE_HOST ; 
 int MUSB_TEST_FORCE_HS ; 
 int MUSB_TEST_J ; 
 int MUSB_TEST_K ; 
 int MUSB_TEST_PACKET ; 
 int MUSB_TEST_SE0_NAK ; 
 int /*<<< orphan*/  OTG_STATE_A_HOST ; 
#define  SetHubFeature 139 
#define  SetPortFeature 138 
#define  USB_PORT_FEAT_C_CONNECTION 137 
#define  USB_PORT_FEAT_C_ENABLE 136 
#define  USB_PORT_FEAT_C_OVER_CURRENT 135 
#define  USB_PORT_FEAT_C_RESET 134 
#define  USB_PORT_FEAT_C_SUSPEND 133 
#define  USB_PORT_FEAT_ENABLE 132 
#define  USB_PORT_FEAT_POWER 131 
#define  USB_PORT_FEAT_RESET 130 
#define  USB_PORT_FEAT_SUSPEND 129 
#define  USB_PORT_FEAT_TEST 128 
 int USB_PORT_STAT_C_SUSPEND ; 
 int USB_PORT_STAT_RESET ; 
 int USB_PORT_STAT_SUSPEND ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  get_unaligned (int*) ; 
 struct musb* hcd_to_musb (struct usb_hcd*) ; 
 int is_host_active (struct musb*) ; 
 int /*<<< orphan*/  is_otg_enabled (struct musb*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  musb_load_testpacket (struct musb*) ; 
 int /*<<< orphan*/  musb_port_reset (struct musb*,int) ; 
 int /*<<< orphan*/  musb_port_suspend (struct musb*,int) ; 
 int musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_set_vbus (struct musb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_start (struct musb*) ; 
 int /*<<< orphan*/  musb_to_hcd (struct musb*) ; 
 int /*<<< orphan*/  musb_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (int /*<<< orphan*/ ) ; 

int musb_hub_control(
	struct usb_hcd	*hcd,
	u16		typeReq,
	u16		wValue,
	u16		wIndex,
	char		*buf,
	u16		wLength)
{
	struct musb	*musb = hcd_to_musb(hcd);
	u32		temp;
	int		retval = 0;
	unsigned long	flags;

	spin_lock_irqsave(&musb->lock, flags);

	if (unlikely(!HCD_HW_ACCESSIBLE(hcd))) {
		spin_unlock_irqrestore(&musb->lock, flags);
		return -ESHUTDOWN;
	}

	/* hub features:  always zero, setting is a NOP
	 * port features: reported, sometimes updated when host is active
	 * no indicators
	 */
	switch (typeReq) {
	case ClearHubFeature:
	case SetHubFeature:
		switch (wValue) {
		case C_HUB_OVER_CURRENT:
		case C_HUB_LOCAL_POWER:
			break;
		default:
			goto error;
		}
		break;
	case ClearPortFeature:
		if ((wIndex & 0xff) != 1)
			goto error;

		switch (wValue) {
		case USB_PORT_FEAT_ENABLE:
			break;
		case USB_PORT_FEAT_SUSPEND:
			musb_port_suspend(musb, false);
			break;
		case USB_PORT_FEAT_POWER:
			if (!(is_otg_enabled(musb) && hcd->self.is_b_host))
				musb_set_vbus(musb, 0);
			break;
		case USB_PORT_FEAT_C_CONNECTION:
		case USB_PORT_FEAT_C_ENABLE:
		case USB_PORT_FEAT_C_OVER_CURRENT:
		case USB_PORT_FEAT_C_RESET:
		case USB_PORT_FEAT_C_SUSPEND:
			break;
		default:
			goto error;
		}
		DBG(5, "clear feature %d\n", wValue);
		musb->port1_status &= ~(1 << wValue);
		break;
	case GetHubDescriptor:
		{
		struct usb_hub_descriptor *desc = (void *)buf;

		desc->bDescLength = 9;
		desc->bDescriptorType = 0x29;
		desc->bNbrPorts = 1;
		desc->wHubCharacteristics = cpu_to_le16(
				  0x0001	/* per-port power switching */
				| 0x0010	/* no overcurrent reporting */
				);
		desc->bPwrOn2PwrGood = 5;	/* msec/2 */
		desc->bHubContrCurrent = 0;

		/* workaround bogus struct definition */
		desc->u.hs.DeviceRemovable[0] = 0x02;	/* port 1 */
		desc->u.hs.DeviceRemovable[1] = 0xff;
		}
		break;
	case GetHubStatus:
		temp = 0;
		*(__le32 *) buf = cpu_to_le32(temp);
		break;
	case GetPortStatus:
		if (wIndex != 1)
			goto error;

		/* finish RESET signaling? */
		if ((musb->port1_status & USB_PORT_STAT_RESET)
				&& time_after_eq(jiffies, musb->rh_timer))
			musb_port_reset(musb, false);

		/* finish RESUME signaling? */
		if ((musb->port1_status & MUSB_PORT_STAT_RESUME)
				&& time_after_eq(jiffies, musb->rh_timer)) {
			u8		power;

			power = musb_readb(musb->mregs, MUSB_POWER);
			power &= ~MUSB_POWER_RESUME;
			DBG(4, "root port resume stopped, power %02x\n",
					power);
			musb_writeb(musb->mregs, MUSB_POWER, power);

			/* ISSUE:  DaVinci (RTL 1.300) disconnects after
			 * resume of high speed peripherals (but not full
			 * speed ones).
			 */

			musb->is_active = 1;
			musb->port1_status &= ~(USB_PORT_STAT_SUSPEND
					| MUSB_PORT_STAT_RESUME);
			musb->port1_status |= USB_PORT_STAT_C_SUSPEND << 16;
			usb_hcd_poll_rh_status(musb_to_hcd(musb));
			/* NOTE: it might really be A_WAIT_BCON ... */
			musb->xceiv->state = OTG_STATE_A_HOST;
		}

		put_unaligned(cpu_to_le32(musb->port1_status
					& ~MUSB_PORT_STAT_RESUME),
				(__le32 *) buf);

		/* port change status is more interesting */
		DBG(get_unaligned((u16 *)(buf+2)) ? 2 : 5, "port status %08x\n",
				musb->port1_status);
		break;
	case SetPortFeature:
		if ((wIndex & 0xff) != 1)
			goto error;

		switch (wValue) {
		case USB_PORT_FEAT_POWER:
			/* NOTE: this controller has a strange state machine
			 * that involves "requesting sessions" according to
			 * magic side effects from incompletely-described
			 * rules about startup...
			 *
			 * This call is what really starts the host mode; be
			 * very careful about side effects if you reorder any
			 * initialization logic, e.g. for OTG, or change any
			 * logic relating to VBUS power-up.
			 */
			if (!(is_otg_enabled(musb) && hcd->self.is_b_host))
				musb_start(musb);
			break;
		case USB_PORT_FEAT_RESET:
			musb_port_reset(musb, true);
			break;
		case USB_PORT_FEAT_SUSPEND:
			musb_port_suspend(musb, true);
			break;
		case USB_PORT_FEAT_TEST:
			if (unlikely(is_host_active(musb)))
				goto error;

			wIndex >>= 8;
			switch (wIndex) {
			case 1:
				pr_debug("TEST_J\n");
				temp = MUSB_TEST_J;
				break;
			case 2:
				pr_debug("TEST_K\n");
				temp = MUSB_TEST_K;
				break;
			case 3:
				pr_debug("TEST_SE0_NAK\n");
				temp = MUSB_TEST_SE0_NAK;
				break;
			case 4:
				pr_debug("TEST_PACKET\n");
				temp = MUSB_TEST_PACKET;
				musb_load_testpacket(musb);
				break;
			case 5:
				pr_debug("TEST_FORCE_ENABLE\n");
				temp = MUSB_TEST_FORCE_HOST
					| MUSB_TEST_FORCE_HS;

				musb_writeb(musb->mregs, MUSB_DEVCTL,
						MUSB_DEVCTL_SESSION);
				break;
			case 6:
				pr_debug("TEST_FIFO_ACCESS\n");
				temp = MUSB_TEST_FIFO_ACCESS;
				break;
			default:
				goto error;
			}
			musb_writeb(musb->mregs, MUSB_TESTMODE, temp);
			break;
		default:
			goto error;
		}
		DBG(5, "set feature %d\n", wValue);
		musb->port1_status |= 1 << wValue;
		break;

	default:
error:
		/* "protocol stall" on error */
		retval = -EPIPE;
	}
	spin_unlock_irqrestore(&musb->lock, flags);
	return retval;
}