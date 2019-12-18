#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct device {int dummy; } ;
struct b3dfg_dev {int transmission_enabled; int cur_dma_frame_idx; int /*<<< orphan*/  buffer_lock; scalar_t__ triplet_ready; int /*<<< orphan*/  triplets_dropped_lock; scalar_t__ triplets_dropped; TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B3D_REG_HW_CTRL ; 
 int /*<<< orphan*/  B3D_REG_WAND_STS ; 
 int EINVAL ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_MASTER ; 
 int /*<<< orphan*/  b3dfg_read32 (struct b3dfg_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b3dfg_write32 (struct b3dfg_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  pci_read_config_word (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int enable_transmission(struct b3dfg_dev *fgdev)
{
	u16 command;
	unsigned long flags;
	struct device *dev = &fgdev->pdev->dev;

	dev_dbg(dev, "enable transmission\n");

	/* check the cable is plugged in. */
	if (!b3dfg_read32(fgdev, B3D_REG_WAND_STS)) {
		dev_dbg(dev, "cannot start transmission without wand\n");
		return -EINVAL;
	}

	/*
	 * Check we're a bus master.
	 * TODO: I think we can remove this having added the pci_set_master call
	 */
	pci_read_config_word(fgdev->pdev, PCI_COMMAND, &command);
	if (!(command & PCI_COMMAND_MASTER)) {
		dev_err(dev, "not a bus master, force-enabling\n");
		pci_write_config_word(fgdev->pdev, PCI_COMMAND,
			command | PCI_COMMAND_MASTER);
	}

	spin_lock_irqsave(&fgdev->buffer_lock, flags);

	/* Handle racing enable_transmission calls. */
	if (fgdev->transmission_enabled) {
		spin_unlock_irqrestore(&fgdev->buffer_lock, flags);
		goto out;
	}

	spin_lock(&fgdev->triplets_dropped_lock);
	fgdev->triplets_dropped = 0;
	spin_unlock(&fgdev->triplets_dropped_lock);

	fgdev->triplet_ready = 0;
	fgdev->cur_dma_frame_idx = -1;
	fgdev->transmission_enabled = 1;

	spin_unlock_irqrestore(&fgdev->buffer_lock, flags);

	/* Enable DMA and cable status interrupts. */
	b3dfg_write32(fgdev, B3D_REG_HW_CTRL, 0x03);

out:
	return 0;
}