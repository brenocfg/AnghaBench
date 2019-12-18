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
struct xhci_virt_device {int /*<<< orphan*/  out_ctx; } ;
struct xhci_hcd {struct xhci_virt_device** devs; } ;
struct usb_device {size_t slot_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  COMP_CTX_STATE 133 
#define  COMP_DEV_ERR 132 
#define  COMP_EBADSLT 131 
#define  COMP_EINVAL 130 
#define  COMP_MEL_ERR 129 
#define  COMP_SUCCESS 128 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xhci_dbg_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*,int) ; 

__attribute__((used)) static int xhci_evaluate_context_result(struct xhci_hcd *xhci,
		struct usb_device *udev, u32 *cmd_status)
{
	int ret;
	struct xhci_virt_device *virt_dev = xhci->devs[udev->slot_id];

	switch (*cmd_status) {
	case COMP_EINVAL:
		dev_warn(&udev->dev, "WARN: xHCI driver setup invalid evaluate "
				"context command.\n");
		ret = -EINVAL;
		break;
	case COMP_EBADSLT:
		dev_warn(&udev->dev, "WARN: slot not enabled for"
				"evaluate context command.\n");
		ret = -EINVAL;
		break;
	case COMP_CTX_STATE:
		dev_warn(&udev->dev, "WARN: invalid context state for "
				"evaluate context command.\n");
		xhci_dbg_ctx(xhci, virt_dev->out_ctx, 1);
		ret = -EINVAL;
		break;
	case COMP_DEV_ERR:
		dev_warn(&udev->dev, "ERROR: Incompatible device for evaluate "
				"context command.\n");
		ret = -ENODEV;
		break;
	case COMP_MEL_ERR:
		/* Max Exit Latency too large error */
		dev_warn(&udev->dev, "WARN: Max Exit Latency too large\n");
		ret = -EINVAL;
		break;
	case COMP_SUCCESS:
		dev_dbg(&udev->dev, "Successful evaluate context command\n");
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