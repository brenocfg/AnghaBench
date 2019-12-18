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
struct usb_ctrlrequest {int bRequest; int bRequestType; int wValue; scalar_t__ wLength; } ;
struct s3c_hsotg_ep {int dir_in; scalar_t__ sent_zlp; } ;
struct s3c_hsotg {int regs; int /*<<< orphan*/  dev; int /*<<< orphan*/  gadget; TYPE_1__* driver; struct s3c_hsotg_ep* eps; } ;
struct TYPE_2__ {int (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
 int S3C_DCFG ; 
 int S3C_DCFG_DevAddr_MASK ; 
 int S3C_DCFG_DevAddr_SHIFT ; 
 int S3C_DIEPCTL0 ; 
 int S3C_DOEPCTL0 ; 
 int S3C_DxEPCTL_CNAK ; 
 int S3C_DxEPCTL_Stall ; 
 int USB_DIR_IN ; 
#define  USB_REQ_CLEAR_FEATURE 131 
#define  USB_REQ_GET_STATUS 130 
#define  USB_REQ_SET_ADDRESS 129 
#define  USB_REQ_SET_FEATURE 128 
 int USB_TYPE_MASK ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int readl (int) ; 
 int s3c_hsotg_process_req_feature (struct s3c_hsotg*,struct usb_ctrlrequest*) ; 
 int s3c_hsotg_process_req_status (struct s3c_hsotg*,struct usb_ctrlrequest*) ; 
 int s3c_hsotg_send_reply (struct s3c_hsotg*,struct s3c_hsotg_ep*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void s3c_hsotg_process_control(struct s3c_hsotg *hsotg,
				      struct usb_ctrlrequest *ctrl)
{
	struct s3c_hsotg_ep *ep0 = &hsotg->eps[0];
	int ret = 0;
	u32 dcfg;

	ep0->sent_zlp = 0;

	dev_dbg(hsotg->dev, "ctrl Req=%02x, Type=%02x, V=%04x, L=%04x\n",
		 ctrl->bRequest, ctrl->bRequestType,
		 ctrl->wValue, ctrl->wLength);

	/* record the direction of the request, for later use when enquing
	 * packets onto EP0. */

	ep0->dir_in = (ctrl->bRequestType & USB_DIR_IN) ? 1 : 0;
	dev_dbg(hsotg->dev, "ctrl: dir_in=%d\n", ep0->dir_in);

	/* if we've no data with this request, then the last part of the
	 * transaction is going to implicitly be IN. */
	if (ctrl->wLength == 0)
		ep0->dir_in = 1;

	if ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) {
		switch (ctrl->bRequest) {
		case USB_REQ_SET_ADDRESS:
			dcfg = readl(hsotg->regs + S3C_DCFG);
			dcfg &= ~S3C_DCFG_DevAddr_MASK;
			dcfg |= ctrl->wValue << S3C_DCFG_DevAddr_SHIFT;
			writel(dcfg, hsotg->regs + S3C_DCFG);

			dev_info(hsotg->dev, "new address %d\n", ctrl->wValue);

			ret = s3c_hsotg_send_reply(hsotg, ep0, NULL, 0);
			return;

		case USB_REQ_GET_STATUS:
			ret = s3c_hsotg_process_req_status(hsotg, ctrl);
			break;

		case USB_REQ_CLEAR_FEATURE:
		case USB_REQ_SET_FEATURE:
			ret = s3c_hsotg_process_req_feature(hsotg, ctrl);
			break;
		}
	}

	/* as a fallback, try delivering it to the driver to deal with */

	if (ret == 0 && hsotg->driver) {
		ret = hsotg->driver->setup(&hsotg->gadget, ctrl);
		if (ret < 0)
			dev_dbg(hsotg->dev, "driver->setup() ret %d\n", ret);
	}

	if (ret > 0) {
		if (!ep0->dir_in) {
			/* need to generate zlp in reply or take data */
			/* todo - deal with any data we might be sent? */
			ret = s3c_hsotg_send_reply(hsotg, ep0, NULL, 0);
		}
	}

	/* the request is either unhandlable, or is not formatted correctly
	 * so respond with a STALL for the status stage to indicate failure.
	 */

	if (ret < 0) {
		u32 reg;
		u32 ctrl;

		dev_dbg(hsotg->dev, "ep0 stall (dir=%d)\n", ep0->dir_in);
		reg = (ep0->dir_in) ? S3C_DIEPCTL0 : S3C_DOEPCTL0;

		/* S3C_DxEPCTL_Stall will be cleared by EP once it has
		 * taken effect, so no need to clear later. */

		ctrl = readl(hsotg->regs + reg);
		ctrl |= S3C_DxEPCTL_Stall;
		ctrl |= S3C_DxEPCTL_CNAK;
		writel(ctrl, hsotg->regs + reg);

		dev_dbg(hsotg->dev,
			"writen DxEPCTL=0x%08x to %08x (DxEPCTL=0x%08x)\n",
			ctrl, reg, readl(hsotg->regs + reg));

		/* don't belive we need to anything more to get the EP
		 * to reply with a STALL packet */
	}
}