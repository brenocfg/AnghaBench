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
typedef  int u8 ;
typedef  int u32 ;
struct device {int dummy; } ;
struct b3dfg_dev {int triplets_dropped; int triplet_ready; int cur_dma_frame_idx; int /*<<< orphan*/  buffer_lock; int /*<<< orphan*/  buffer_queue; int /*<<< orphan*/  triplets_dropped_lock; int /*<<< orphan*/  transmission_enabled; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B3D_REG_DMA_STS ; 
 int /*<<< orphan*/  B3D_REG_EC220_DMA_STS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int b3dfg_read32 (struct b3dfg_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b3dfg_write32 (struct b3dfg_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  handle_cstate_change (struct b3dfg_dev*) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int setup_next_frame_transfer (struct b3dfg_dev*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transfer_complete (struct b3dfg_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t b3dfg_intr(int irq, void *dev_id)
{
	struct b3dfg_dev *fgdev = dev_id;
	struct device *dev = &fgdev->pdev->dev;
	u32 sts;
	u8 dropped;
	bool need_ack = 1;
	irqreturn_t res = IRQ_HANDLED;

	sts = b3dfg_read32(fgdev, B3D_REG_DMA_STS);
	if (unlikely(sts == 0)) {
		dev_warn(dev, "ignore interrupt, DMA status is 0\n");
		res = IRQ_NONE;
		goto out;
	}

	if (unlikely(!fgdev->transmission_enabled)) {
		dev_warn(dev, "ignore interrupt, TX disabled\n");
		res = IRQ_HANDLED;
		goto out;
	}

	/* Handle dropped frames, as reported by the hardware. */
	dropped = (sts >> 8) & 0xff;
	dev_dbg(dev, "intr: DMA_STS=%08x (drop=%d comp=%d next=%d)\n",
		sts, dropped, !!(sts & 0x4), sts & 0x3);
	if (unlikely(dropped > 0)) {
		spin_lock(&fgdev->triplets_dropped_lock);
		fgdev->triplets_dropped += dropped;
		spin_unlock(&fgdev->triplets_dropped_lock);
	}

	/* Handle a cable state change (i.e. the wand being unplugged). */
	if (sts & 0x08) {
		handle_cstate_change(fgdev);
		goto out;
	}

	spin_lock(&fgdev->buffer_lock);
	if (unlikely(list_empty(&fgdev->buffer_queue))) {

		/* FIXME need more sanity checking here */
		dev_info(dev, "buffer not ready for next transfer\n");
		fgdev->triplet_ready = 1;
		goto out_unlock;
	}

	/* Has a frame transfer been completed? */
	if (sts & 0x4) {
		u32 dma_status = b3dfg_read32(fgdev, B3D_REG_EC220_DMA_STS);

		/* Check for DMA errors reported by the hardware. */
		if (unlikely(dma_status & 0x1)) {
			dev_err(dev, "EC220 error: %08x\n", dma_status);

			/* FIXME flesh out error handling */
			goto out_unlock;
		}

		/* Sanity check, we should have a frame index at this point. */
		if (unlikely(fgdev->cur_dma_frame_idx == -1)) {
			dev_err(dev, "completed but no last idx?\n");

			/* FIXME flesh out error handling */
			goto out_unlock;
		}

		transfer_complete(fgdev);
	}

	/* Is there another frame transfer pending? */
	if (sts & 0x3)
		need_ack = setup_next_frame_transfer(fgdev, sts & 0x3);
	else
		fgdev->cur_dma_frame_idx = -1;

out_unlock:
	spin_unlock(&fgdev->buffer_lock);
out:
	if (need_ack) {
		dev_dbg(dev, "acknowledging interrupt\n");
		b3dfg_write32(fgdev, B3D_REG_EC220_DMA_STS, 0x0b);
	}
	return res;
}