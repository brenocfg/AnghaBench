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
typedef  int u32 ;
struct xhci_hcd {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  COMP_2ND_BW_ERR 133 
#define  COMP_BW_ERR 132 
#define  COMP_DEV_ERR 131 
#define  COMP_ENOMEM 130 
#define  COMP_SUCCESS 129 
#define  COMP_TRB_ERR 128 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*,int) ; 

__attribute__((used)) static int xhci_configure_endpoint_result(struct xhci_hcd *xhci,
		struct usb_device *udev, u32 *cmd_status)
{
	int ret;

	switch (*cmd_status) {
	case COMP_ENOMEM:
		dev_warn(&udev->dev, "Not enough host controller resources "
				"for new device state.\n");
		ret = -ENOMEM;
		/* FIXME: can we allocate more resources for the HC? */
		break;
	case COMP_BW_ERR:
	case COMP_2ND_BW_ERR:
		dev_warn(&udev->dev, "Not enough bandwidth "
				"for new device state.\n");
		ret = -ENOSPC;
		/* FIXME: can we go back to the old state? */
		break;
	case COMP_TRB_ERR:
		/* the HCD set up something wrong */
		dev_warn(&udev->dev, "ERROR: Endpoint drop flag = 0, "
				"add flag = 1, "
				"and endpoint is not disabled.\n");
		ret = -EINVAL;
		break;
	case COMP_DEV_ERR:
		dev_warn(&udev->dev, "ERROR: Incompatible device for endpoint "
				"configure command.\n");
		ret = -ENODEV;
		break;
	case COMP_SUCCESS:
		dev_dbg(&udev->dev, "Successful Endpoint Configure command\n");
		ret = 0;
		break;
	default:
		xhci_err(xhci, "ERROR: unexpected command completion "
				"code 0x%x.\n", *cmd_status);
		ret = -EINVAL;
		break;
	}
	return ret;
}