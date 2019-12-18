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
typedef  int /*<<< orphan*/  u32 ;
struct usb_hcd {scalar_t__ regs; int /*<<< orphan*/  state; } ;
struct isp1760_hcd {int /*<<< orphan*/  next_statechange; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESET ; 
 int /*<<< orphan*/  HC_STATE_HALT ; 
 scalar_t__ HC_USBCMD ; 
 int handshake (struct isp1760_hcd*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isp1760_readl (scalar_t__) ; 
 int /*<<< orphan*/  isp1760_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jiffies ; 
 struct usb_hcd* priv_to_hcd (struct isp1760_hcd*) ; 

__attribute__((used)) static int ehci_reset(struct isp1760_hcd *priv)
{
	int retval;
	struct usb_hcd *hcd = priv_to_hcd(priv);
	u32 command = isp1760_readl(hcd->regs + HC_USBCMD);

	command |= CMD_RESET;
	isp1760_writel(command, hcd->regs + HC_USBCMD);
	hcd->state = HC_STATE_HALT;
	priv->next_statechange = jiffies;
	retval = handshake(priv, hcd->regs + HC_USBCMD,
			    CMD_RESET, 0, 250 * 1000);
	return retval;
}