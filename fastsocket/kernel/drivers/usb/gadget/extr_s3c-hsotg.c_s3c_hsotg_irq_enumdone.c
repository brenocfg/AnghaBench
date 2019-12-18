#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct s3c_hsotg {scalar_t__ regs; int /*<<< orphan*/  dev; TYPE_1__ gadget; } ;

/* Variables and functions */
 int EP0_MPS_LIMIT ; 
 scalar_t__ S3C_DIEPCTL0 ; 
 scalar_t__ S3C_DOEPCTL0 ; 
 scalar_t__ S3C_DSTS ; 
#define  S3C_DSTS_EnumSpd_FS 131 
#define  S3C_DSTS_EnumSpd_FS48 130 
#define  S3C_DSTS_EnumSpd_HS 129 
#define  S3C_DSTS_EnumSpd_LS 128 
 int S3C_DSTS_EnumSpd_MASK ; 
 int S3C_HSOTG_EPS ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_LOW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  s3c_hsotg_enqueue_setup (struct s3c_hsotg*) ; 
 int /*<<< orphan*/  s3c_hsotg_set_ep_maxpacket (struct s3c_hsotg*,int,int) ; 

__attribute__((used)) static void s3c_hsotg_irq_enumdone(struct s3c_hsotg *hsotg)
{
	u32 dsts = readl(hsotg->regs + S3C_DSTS);
	int ep0_mps = 0, ep_mps;

	/* This should signal the finish of the enumeration phase
	 * of the USB handshaking, so we should now know what rate
	 * we connected at. */

	dev_dbg(hsotg->dev, "EnumDone (DSTS=0x%08x)\n", dsts);

	/* note, since we're limited by the size of transfer on EP0, and
	 * it seems IN transfers must be a even number of packets we do
	 * not advertise a 64byte MPS on EP0. */

	/* catch both EnumSpd_FS and EnumSpd_FS48 */
	switch (dsts & S3C_DSTS_EnumSpd_MASK) {
	case S3C_DSTS_EnumSpd_FS:
	case S3C_DSTS_EnumSpd_FS48:
		hsotg->gadget.speed = USB_SPEED_FULL;
		dev_info(hsotg->dev, "new device is full-speed\n");

		ep0_mps = EP0_MPS_LIMIT;
		ep_mps = 64;
		break;

	case S3C_DSTS_EnumSpd_HS:
		dev_info(hsotg->dev, "new device is high-speed\n");
		hsotg->gadget.speed = USB_SPEED_HIGH;

		ep0_mps = EP0_MPS_LIMIT;
		ep_mps = 512;
		break;

	case S3C_DSTS_EnumSpd_LS:
		hsotg->gadget.speed = USB_SPEED_LOW;
		dev_info(hsotg->dev, "new device is low-speed\n");

		/* note, we don't actually support LS in this driver at the
		 * moment, and the documentation seems to imply that it isn't
		 * supported by the PHYs on some of the devices.
		 */
		break;
	}

	/* we should now know the maximum packet size for an
	 * endpoint, so set the endpoints to a default value. */

	if (ep0_mps) {
		int i;
		s3c_hsotg_set_ep_maxpacket(hsotg, 0, ep0_mps);
		for (i = 1; i < S3C_HSOTG_EPS; i++)
			s3c_hsotg_set_ep_maxpacket(hsotg, i, ep_mps);
	}

	/* ensure after enumeration our EP0 is active */

	s3c_hsotg_enqueue_setup(hsotg);

	dev_dbg(hsotg->dev, "EP0: DIEPCTL0=0x%08x, DOEPCTL0=0x%08x\n",
		readl(hsotg->regs + S3C_DIEPCTL0),
		readl(hsotg->regs + S3C_DOEPCTL0));
}