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
struct qlcnic_adapter {TYPE_2__* ahw; } ;
struct qlc_83xx_quad_entry {unsigned long dr_addr; int /*<<< orphan*/  ar_addr; int /*<<< orphan*/  ar_value; } ;
struct qlc_83xx_poll {int /*<<< orphan*/  status; int /*<<< orphan*/  mask; } ;
struct qlc_83xx_entry_hdr {int count; scalar_t__ delay; } ;
struct TYPE_3__ {int array_index; int* array; } ;
struct TYPE_4__ {TYPE_1__ reset; } ;

/* Variables and functions */
 int QLC_83XX_MAX_RESET_SEQ_ENTRIES ; 
 int /*<<< orphan*/  qlcnic_83xx_poll_reg (struct qlcnic_adapter*,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qlcnic_83xx_rd_reg_indirect (struct qlcnic_adapter*,unsigned long) ; 
 int /*<<< orphan*/  qlcnic_83xx_wrt_reg_indirect (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlcnic_83xx_poll_read_list(struct qlcnic_adapter *p_dev,
				       struct qlc_83xx_entry_hdr *p_hdr)
{
	long delay;
	int index, i, j;
	struct qlc_83xx_quad_entry *entry;
	struct qlc_83xx_poll *poll;
	unsigned long addr;

	poll = (struct qlc_83xx_poll *)((char *)p_hdr +
					sizeof(struct qlc_83xx_entry_hdr));

	entry = (struct qlc_83xx_quad_entry *)((char *)poll +
					       sizeof(struct qlc_83xx_poll));
	delay = (long)p_hdr->delay;

	for (i = 0; i < p_hdr->count; i++, entry++) {
		qlcnic_83xx_wrt_reg_indirect(p_dev, entry->ar_addr,
					     entry->ar_value);
		if (delay) {
			if (!qlcnic_83xx_poll_reg(p_dev, entry->ar_addr, delay,
						  poll->mask, poll->status)){
				index = p_dev->ahw->reset.array_index;
				addr = entry->dr_addr;
				j = qlcnic_83xx_rd_reg_indirect(p_dev, addr);
				p_dev->ahw->reset.array[index++] = j;

				if (index == QLC_83XX_MAX_RESET_SEQ_ENTRIES)
					p_dev->ahw->reset.array_index = 1;
			}
		}
	}
}