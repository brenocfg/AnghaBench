#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct jme_adapter {TYPE_1__* pdev; int /*<<< orphan*/  flags; struct net_device* dev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int IRQF_SHARED ; 
 int /*<<< orphan*/  JME_FLAG_MSI ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jeprintk (TYPE_1__*,char*,char*,int) ; 
 int /*<<< orphan*/  jme_intr ; 
 int /*<<< orphan*/  jme_msi ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_enable_msi (TYPE_1__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_request_irq(struct jme_adapter *jme)
{
	int rc;
	struct net_device *netdev = jme->dev;
	irq_handler_t handler = jme_intr;
	int irq_flags = IRQF_SHARED;

	if (!pci_enable_msi(jme->pdev)) {
		set_bit(JME_FLAG_MSI, &jme->flags);
		handler = jme_msi;
		irq_flags = 0;
	}

	rc = request_irq(jme->pdev->irq, handler, irq_flags, netdev->name,
			  netdev);
	if (rc) {
		jeprintk(jme->pdev,
			"Unable to request %s interrupt (return: %d)\n",
			test_bit(JME_FLAG_MSI, &jme->flags) ? "MSI" : "INTx",
			rc);

		if (test_bit(JME_FLAG_MSI, &jme->flags)) {
			pci_disable_msi(jme->pdev);
			clear_bit(JME_FLAG_MSI, &jme->flags);
		}
	} else {
		netdev->irq = jme->pdev->irq;
	}

	return rc;
}