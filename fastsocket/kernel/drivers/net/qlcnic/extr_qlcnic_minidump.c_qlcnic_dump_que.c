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
struct __queue {int read_addr; int read_addr_cnt; int no_ops; scalar_t__ stride; scalar_t__ read_addr_stride; int /*<<< orphan*/  sel_addr; } ;
struct TYPE_2__ {struct __queue que; } ;
struct qlcnic_dump_entry {TYPE_1__ region; } ;
struct qlcnic_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int qlcnic_ind_rd (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_ind_wr (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 qlcnic_dump_que(struct qlcnic_adapter *adapter,
			   struct qlcnic_dump_entry *entry, __le32 *buffer)
{
	int i, loop;
	u32 cnt, addr, data, que_id = 0;
	struct __queue *que = &entry->region.que;

	addr = que->read_addr;
	cnt = que->read_addr_cnt;

	for (loop = 0; loop < que->no_ops; loop++) {
		qlcnic_ind_wr(adapter, que->sel_addr, que_id);
		addr = que->read_addr;
		for (i = 0; i < cnt; i++) {
			data = qlcnic_ind_rd(adapter, addr);
			*buffer++ = cpu_to_le32(data);
			addr += que->read_addr_stride;
		}
		que_id += que->stride;
	}
	return que->no_ops * cnt * sizeof(u32);
}