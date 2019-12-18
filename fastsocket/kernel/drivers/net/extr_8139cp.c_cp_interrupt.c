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
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct cp_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  pdev; int /*<<< orphan*/  mii_if; int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  Cmd ; 
 int /*<<< orphan*/  CpCmd ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  IntrStatus ; 
 int LinkChg ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int PciErr ; 
 int RxEmpty ; 
 int RxErr ; 
 int RxFIFOOvr ; 
 int RxOK ; 
 int SWInt ; 
 int TxEmpty ; 
 int TxErr ; 
 int TxOK ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_norx_intr_mask ; 
 int cp_rx_intr_mask ; 
 int /*<<< orphan*/  cp_tx (struct cp_private*) ; 
 int cpr16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpr8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpw16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpw16_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_intr (struct cp_private*) ; 
 int /*<<< orphan*/  netif_msg_link (struct cp_private*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t cp_interrupt (int irq, void *dev_instance)
{
	struct net_device *dev = dev_instance;
	struct cp_private *cp;
	int handled = 0;
	u16 status;

	if (unlikely(dev == NULL))
		return IRQ_NONE;
	cp = netdev_priv(dev);

	spin_lock(&cp->lock);

	status = cpr16(IntrStatus);
	if (!status || (status == 0xFFFF))
		goto out_unlock;

	handled = 1;

	if (netif_msg_intr(cp))
		pr_debug("%s: intr, status %04x cmd %02x cpcmd %04x\n",
		        dev->name, status, cpr8(Cmd), cpr16(CpCmd));

	cpw16(IntrStatus, status & ~cp_rx_intr_mask);

	/* close possible race's with dev_close */
	if (unlikely(!netif_running(dev))) {
		cpw16(IntrMask, 0);
		goto out_unlock;
	}

	if (status & (RxOK | RxErr | RxEmpty | RxFIFOOvr))
		if (napi_schedule_prep(&cp->napi)) {
			cpw16_f(IntrMask, cp_norx_intr_mask);
			__napi_schedule(&cp->napi);
		}

	if (status & (TxOK | TxErr | TxEmpty | SWInt))
		cp_tx(cp);
	if (status & LinkChg)
		mii_check_media(&cp->mii_if, netif_msg_link(cp), false);


	if (status & PciErr) {
		u16 pci_status;

		pci_read_config_word(cp->pdev, PCI_STATUS, &pci_status);
		pci_write_config_word(cp->pdev, PCI_STATUS, pci_status);
		pr_err("%s: PCI bus error, status=%04x, PCI status=%04x\n",
		       dev->name, status, pci_status);

		/* TODO: reset hardware */
	}

out_unlock:
	spin_unlock(&cp->lock);

	return IRQ_RETVAL(handled);
}