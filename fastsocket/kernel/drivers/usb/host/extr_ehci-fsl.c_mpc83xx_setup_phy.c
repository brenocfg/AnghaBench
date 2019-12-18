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
typedef  int /*<<< orphan*/  u32 ;
struct ehci_hcd {TYPE_1__* regs; } ;
typedef  enum fsl_usb2_phy_modes { ____Placeholder_fsl_usb2_phy_modes } fsl_usb2_phy_modes ;
struct TYPE_2__ {int /*<<< orphan*/ * port_status; } ;

/* Variables and functions */
#define  FSL_USB2_PHY_NONE 132 
#define  FSL_USB2_PHY_SERIAL 131 
#define  FSL_USB2_PHY_ULPI 130 
#define  FSL_USB2_PHY_UTMI 129 
#define  FSL_USB2_PHY_UTMI_WIDE 128 
 int /*<<< orphan*/  PORT_PTS_PTW ; 
 int /*<<< orphan*/  PORT_PTS_SERIAL ; 
 int /*<<< orphan*/  PORT_PTS_ULPI ; 
 int /*<<< orphan*/  PORT_PTS_UTMI ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mpc83xx_setup_phy(struct ehci_hcd *ehci,
			      enum fsl_usb2_phy_modes phy_mode,
			      unsigned int port_offset)
{
	u32 portsc = 0;
	switch (phy_mode) {
	case FSL_USB2_PHY_ULPI:
		portsc |= PORT_PTS_ULPI;
		break;
	case FSL_USB2_PHY_SERIAL:
		portsc |= PORT_PTS_SERIAL;
		break;
	case FSL_USB2_PHY_UTMI_WIDE:
		portsc |= PORT_PTS_PTW;
		/* fall through */
	case FSL_USB2_PHY_UTMI:
		portsc |= PORT_PTS_UTMI;
		break;
	case FSL_USB2_PHY_NONE:
		break;
	}
	ehci_writel(ehci, portsc, &ehci->regs->port_status[port_offset]);
}