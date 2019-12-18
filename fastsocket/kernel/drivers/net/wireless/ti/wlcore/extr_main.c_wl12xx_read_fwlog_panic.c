#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct wl1271_rx_descriptor {int dummy; } ;
struct TYPE_4__ {scalar_t__ mem_blocks; scalar_t__ output; scalar_t__ mode; } ;
struct TYPE_5__ {TYPE_1__ fwlog; } ;
struct wl1271 {int quirks; int /*<<< orphan*/  fwlog_waitq; TYPE_2__ conf; TYPE_3__* fw_status_2; int /*<<< orphan*/  fw_status_1; int /*<<< orphan*/  watchdog_recovery; } ;
typedef  int /*<<< orphan*/  addr ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {int /*<<< orphan*/  log_start_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WL12XX_FWLOG_CONTINUOUS ; 
 scalar_t__ WL12XX_FWLOG_OUTPUT_DBG_PINS ; 
 scalar_t__ WL12XX_HW_BLOCK_SIZE ; 
 scalar_t__ WLCORE_FW_LOG_END ; 
 int WLCORE_QUIRK_FWLOG_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_info (char*) ; 
 scalar_t__ wl1271_ps_elp_wakeup (struct wl1271*) ; 
 int /*<<< orphan*/  wl12xx_cmd_stop_fwlog (struct wl1271*) ; 
 int /*<<< orphan*/  wl12xx_copy_fwlog (struct wl1271*,int /*<<< orphan*/ *,scalar_t__) ; 
 int wlcore_fw_status (struct wl1271*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int wlcore_read_hwaddr (struct wl1271*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void wl12xx_read_fwlog_panic(struct wl1271 *wl)
{
	u32 addr;
	u32 offset;
	u32 end_of_log;
	u8 *block;
	int ret;

	if ((wl->quirks & WLCORE_QUIRK_FWLOG_NOT_IMPLEMENTED) ||
	    (wl->conf.fwlog.mem_blocks == 0))
		return;

	wl1271_info("Reading FW panic log");

	block = kmalloc(WL12XX_HW_BLOCK_SIZE, GFP_KERNEL);
	if (!block)
		return;

	/*
	 * Make sure the chip is awake and the logger isn't active.
	 * Do not send a stop fwlog command if the fw is hanged or if
	 * dbgpins are used (due to some fw bug).
	 */
	if (wl1271_ps_elp_wakeup(wl))
		goto out;
	if (!wl->watchdog_recovery &&
	    wl->conf.fwlog.output != WL12XX_FWLOG_OUTPUT_DBG_PINS)
		wl12xx_cmd_stop_fwlog(wl);

	/* Read the first memory block address */
	ret = wlcore_fw_status(wl, wl->fw_status_1, wl->fw_status_2);
	if (ret < 0)
		goto out;

	addr = le32_to_cpu(wl->fw_status_2->log_start_addr);
	if (!addr)
		goto out;

	if (wl->conf.fwlog.mode == WL12XX_FWLOG_CONTINUOUS) {
		offset = sizeof(addr) + sizeof(struct wl1271_rx_descriptor);
		end_of_log = WLCORE_FW_LOG_END;
	} else {
		offset = sizeof(addr);
		end_of_log = addr;
	}

	/* Traverse the memory blocks linked list */
	do {
		memset(block, 0, WL12XX_HW_BLOCK_SIZE);
		ret = wlcore_read_hwaddr(wl, addr, block, WL12XX_HW_BLOCK_SIZE,
					 false);
		if (ret < 0)
			goto out;

		/*
		 * Memory blocks are linked to one another. The first 4 bytes
		 * of each memory block hold the hardware address of the next
		 * one. The last memory block points to the first one in
		 * on demand mode and is equal to 0x2000000 in continuous mode.
		 */
		addr = le32_to_cpup((__le32 *)block);
		if (!wl12xx_copy_fwlog(wl, block + offset,
				       WL12XX_HW_BLOCK_SIZE - offset))
			break;
	} while (addr && (addr != end_of_log));

	wake_up_interruptible(&wl->fwlog_waitq);

out:
	kfree(block);
}