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
struct device {int dummy; } ;
struct b3dfg_dev {int /*<<< orphan*/  buffer_waitqueue; int /*<<< orphan*/  buffer_lock; scalar_t__ transmission_enabled; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B3D_REG_DMA_STS ; 
 int /*<<< orphan*/  B3D_REG_HW_CTRL ; 
 int /*<<< orphan*/  b3dfg_read32 (struct b3dfg_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b3dfg_write32 (struct b3dfg_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dequeue_all_buffers (struct b3dfg_dev*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_transmission(struct b3dfg_dev *fgdev)
{
	struct device *dev = &fgdev->pdev->dev;
	unsigned long flags;
	u32 tmp;

	dev_dbg(dev, "disable transmission\n");

	/* guarantee that no more interrupts will be serviced */
	spin_lock_irqsave(&fgdev->buffer_lock, flags);
	fgdev->transmission_enabled = 0;

	b3dfg_write32(fgdev, B3D_REG_HW_CTRL, 0);

	/* FIXME: temporary debugging only. if the board stops transmitting,
	 * hitting ctrl+c and seeing this message is useful for determining
	 * the state of the board. */
	tmp = b3dfg_read32(fgdev, B3D_REG_DMA_STS);
	dev_dbg(dev, "DMA_STS reads %x after TX stopped\n", tmp);

	dequeue_all_buffers(fgdev);
	spin_unlock_irqrestore(&fgdev->buffer_lock, flags);

	wake_up_interruptible(&fgdev->buffer_waitqueue);
}