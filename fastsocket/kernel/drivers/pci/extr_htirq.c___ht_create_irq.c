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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int address_lo; int address_hi; } ;
struct ht_irq_cfg {int pos; int idx; TYPE_1__ msg; int /*<<< orphan*/ * update; struct pci_dev* dev; } ;
typedef  int /*<<< orphan*/  ht_irq_update_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HT_CAPTYPE_IRQ ; 
 scalar_t__ arch_setup_ht_irq (int,struct pci_dev*) ; 
 int create_irq_nr (int /*<<< orphan*/ ,int) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ht_destroy_irq (int) ; 
 int /*<<< orphan*/  ht_irq_lock ; 
 int /*<<< orphan*/  kfree (struct ht_irq_cfg*) ; 
 struct ht_irq_cfg* kmalloc (int,int /*<<< orphan*/ ) ; 
 int pci_find_ht_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  set_irq_data (int,struct ht_irq_cfg*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int __ht_create_irq(struct pci_dev *dev, int idx, ht_irq_update_t *update)
{
	struct ht_irq_cfg *cfg;
	unsigned long flags;
	u32 data;
	int max_irq;
	int pos;
	int irq;
	int node;

	pos = pci_find_ht_capability(dev, HT_CAPTYPE_IRQ);
	if (!pos)
		return -EINVAL;

	/* Verify the idx I want to use is in range */
	spin_lock_irqsave(&ht_irq_lock, flags);
	pci_write_config_byte(dev, pos + 2, 1);
	pci_read_config_dword(dev, pos + 4, &data);
	spin_unlock_irqrestore(&ht_irq_lock, flags);

	max_irq = (data >> 16) & 0xff;
	if ( idx > max_irq)
		return -EINVAL;

	cfg = kmalloc(sizeof(*cfg), GFP_KERNEL);
	if (!cfg)
		return -ENOMEM;

	cfg->dev = dev;
	cfg->update = update;
	cfg->pos = pos;
	cfg->idx = 0x10 + (idx * 2);
	/* Initialize msg to a value that will never match the first write. */
	cfg->msg.address_lo = 0xffffffff;
	cfg->msg.address_hi = 0xffffffff;

	node = dev_to_node(&dev->dev);
	irq = create_irq_nr(0, node);

	if (irq <= 0) {
		kfree(cfg);
		return -EBUSY;
	}
	set_irq_data(irq, cfg);

	if (arch_setup_ht_irq(irq, dev) < 0) {
		ht_destroy_irq(irq);
		return -EBUSY;
	}

	return irq;
}