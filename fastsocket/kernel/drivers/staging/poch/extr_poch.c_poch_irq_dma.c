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
typedef  unsigned long u32 ;
struct poch_group_info {int /*<<< orphan*/  user_offset; } ;
struct channel_info {unsigned long transfer; scalar_t__ chno; unsigned long fpga_iomem; long group_count; int /*<<< orphan*/  wq; int /*<<< orphan*/  group_offsets_lock; struct poch_group_info* groups; TYPE_1__* header; int /*<<< orphan*/  inited; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/ * group_offsets; } ;

/* Variables and functions */
 scalar_t__ CHNO_RX_CHANNEL ; 
 unsigned long FPGA_RX_CURR_GROUP_REG ; 
 unsigned long FPGA_TX_CURR_GROUP_REG ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 unsigned long ioread32 (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void poch_irq_dma(struct channel_info *channel)
{
	u32 prev_transfer;
	u32 curr_transfer;
	long groups_done;
	unsigned long i, j;
	struct poch_group_info *groups;
	s32 *group_offsets;
	u32 curr_group_reg;

	if (!atomic_read(&channel->inited))
		return;

	prev_transfer = channel->transfer;

	if (channel->chno == CHNO_RX_CHANNEL)
		curr_group_reg = FPGA_RX_CURR_GROUP_REG;
	else
		curr_group_reg = FPGA_TX_CURR_GROUP_REG;

	curr_transfer = ioread32(channel->fpga_iomem + curr_group_reg);

	groups_done = curr_transfer - prev_transfer;
	/* Check wrap over, and handle it. */
	if (groups_done <= 0)
		groups_done += channel->group_count;

	group_offsets = channel->header->group_offsets;
	groups = channel->groups;

	spin_lock(&channel->group_offsets_lock);

	for (i = 0; i < groups_done; i++) {
		j = (prev_transfer + i) % channel->group_count;
		group_offsets[j] = groups[j].user_offset;
	}

	spin_unlock(&channel->group_offsets_lock);

	channel->transfer = curr_transfer;

	wake_up_interruptible(&channel->wq);
}