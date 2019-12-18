#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  speed; } ;
struct udc {scalar_t__ data_ep_queued; scalar_t__ data_ep_enabled; TYPE_2__* regs; TYPE_1__ gadget; } ;
struct TYPE_4__ {int /*<<< orphan*/  cfg; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMD_UNMASK_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (struct udc*,char*) ; 
 int /*<<< orphan*/  UDC_DEVCFG_CSR_PRG ; 
 int /*<<< orphan*/  UDC_DEVCFG_RWKP ; 
 int /*<<< orphan*/  UDC_DEVCFG_SP ; 
 int /*<<< orphan*/  UDC_DEVCTL_RDE ; 
 int /*<<< orphan*/  UDC_DEVCTL_TDE ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  make_ep_lists (struct udc*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 scalar_t__ set_rde ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_pollstall_timer ; 
 int /*<<< orphan*/  udc_timer ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void udc_basic_init(struct udc *dev)
{
	u32	tmp;

	DBG(dev, "udc_basic_init()\n");

	dev->gadget.speed = USB_SPEED_UNKNOWN;

	/* stop RDE timer */
	if (timer_pending(&udc_timer)) {
		set_rde = 0;
		mod_timer(&udc_timer, jiffies - 1);
	}
	/* stop poll stall timer */
	if (timer_pending(&udc_pollstall_timer)) {
		mod_timer(&udc_pollstall_timer, jiffies - 1);
	}
	/* disable DMA */
	tmp = readl(&dev->regs->ctl);
	tmp &= AMD_UNMASK_BIT(UDC_DEVCTL_RDE);
	tmp &= AMD_UNMASK_BIT(UDC_DEVCTL_TDE);
	writel(tmp, &dev->regs->ctl);

	/* enable dynamic CSR programming */
	tmp = readl(&dev->regs->cfg);
	tmp |= AMD_BIT(UDC_DEVCFG_CSR_PRG);
	/* set self powered */
	tmp |= AMD_BIT(UDC_DEVCFG_SP);
	/* set remote wakeupable */
	tmp |= AMD_BIT(UDC_DEVCFG_RWKP);
	writel(tmp, &dev->regs->cfg);

	make_ep_lists(dev);

	dev->data_ep_enabled = 0;
	dev->data_ep_queued = 0;
}