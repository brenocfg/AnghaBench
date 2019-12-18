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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct mvs_slot_info {size_t tx; int cmd_size; int n_elem; scalar_t__ buf_dma; scalar_t__ buf; } ;
struct mvs_info {size_t tx_prod; int /*<<< orphan*/  dev; scalar_t__ slot_dma; int /*<<< orphan*/ * slot; scalar_t__ tx_dma; int /*<<< orphan*/ * tx; struct mvs_slot_info* slot_info; } ;
struct mvs_cmd_hdr {int dummy; } ;
typedef  enum sas_protocol { ____Placeholder_sas_protocol } sas_protocol ;
struct TYPE_2__ {int (* prd_size ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 TYPE_1__* MVS_CHIP_DISP ; 
 size_t MVS_CHIP_SLOT_SZ ; 
 int MVS_OAF_SZ ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mvs_hba_sb_dump (struct mvs_info*,size_t,int) ; 
 int /*<<< orphan*/  mvs_hexdump (int,int /*<<< orphan*/ *,size_t) ; 
 int stub1 () ; 

__attribute__((used)) static void mvs_hba_memory_dump(struct mvs_info *mvi, u32 tag,
				enum sas_protocol proto)
{
#if (_MV_DUMP > 1)
	u32 sz, w_ptr;
	u64 addr;
	struct mvs_slot_info *slot = &mvi->slot_info[tag];

	/*Delivery Queue */
	sz = MVS_CHIP_SLOT_SZ;
	w_ptr = slot->tx;
	addr = mvi->tx_dma;
	dev_printk(KERN_DEBUG, mvi->dev,
		"Delivery Queue Size=%04d , WRT_PTR=%04X\n", sz, w_ptr);
	dev_printk(KERN_DEBUG, mvi->dev,
		"Delivery Queue Base Address=0x%llX (PA)"
		"(tx_dma=0x%llX), Entry=%04d\n",
		addr, (unsigned long long)mvi->tx_dma, w_ptr);
	mvs_hexdump(sizeof(u32), (u8 *)(&mvi->tx[mvi->tx_prod]),
			(u32) mvi->tx_dma + sizeof(u32) * w_ptr);
	/*Command List */
	addr = mvi->slot_dma;
	dev_printk(KERN_DEBUG, mvi->dev,
		"Command List Base Address=0x%llX (PA)"
		"(slot_dma=0x%llX), Header=%03d\n",
		addr, (unsigned long long)slot->buf_dma, tag);
	dev_printk(KERN_DEBUG, mvi->dev, "Command Header[%03d]:\n", tag);
	/*mvs_cmd_hdr */
	mvs_hexdump(sizeof(struct mvs_cmd_hdr), (u8 *)(&mvi->slot[tag]),
		(u32) mvi->slot_dma + tag * sizeof(struct mvs_cmd_hdr));
	/*1.command table area */
	dev_printk(KERN_DEBUG, mvi->dev, "+---->Command Table :\n");
	mvs_hexdump(slot->cmd_size, (u8 *) slot->buf, (u32) slot->buf_dma);
	/*2.open address frame area */
	dev_printk(KERN_DEBUG, mvi->dev, "+---->Open Address Frame :\n");
	mvs_hexdump(MVS_OAF_SZ, (u8 *) slot->buf + slot->cmd_size,
				(u32) slot->buf_dma + slot->cmd_size);
	/*3.status buffer */
	mvs_hba_sb_dump(mvi, tag, proto);
	/*4.PRD table */
	dev_printk(KERN_DEBUG, mvi->dev, "+---->PRD table :\n");
	mvs_hexdump(MVS_CHIP_DISP->prd_size() * slot->n_elem,
		(u8 *) slot->buf + slot->cmd_size + MVS_OAF_SZ,
		(u32) slot->buf_dma + slot->cmd_size + MVS_OAF_SZ);
#endif
}