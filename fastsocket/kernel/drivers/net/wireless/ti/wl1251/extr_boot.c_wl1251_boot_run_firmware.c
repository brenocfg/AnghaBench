#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct wl1251 {scalar_t__ chip_id; int event_mask; scalar_t__ intr_mask; int /*<<< orphan*/  fw_ver; void* event_box_addr; void* cmd_box_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_REG_INTERRUPT_ACK ; 
 int /*<<< orphan*/  ACX_REG_INTERRUPT_NO_CLEAR ; 
 int BSS_LOSE_EVENT_ID ; 
 int BT_PTA_PREDICTION_EVENT_ID ; 
 int BT_PTA_SENSE_EVENT_ID ; 
 int /*<<< orphan*/  CHIP_ID_B ; 
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int /*<<< orphan*/  DEBUG_MAILBOX ; 
 int /*<<< orphan*/  ECPU_CONTROL_HALT ; 
 int EIO ; 
 int INIT_LOOP ; 
 int /*<<< orphan*/  INIT_LOOP_DELAY ; 
 int JOIN_EVENT_COMPLETE_ID ; 
 int REGAINED_BSS_EVENT_ID ; 
 int /*<<< orphan*/  REG_COMMAND_MAILBOX_PTR ; 
 int /*<<< orphan*/  REG_EVENT_MAILBOX_PTR ; 
 int ROAMING_TRIGGER_LOW_RSSI_EVENT_ID ; 
 int ROAMING_TRIGGER_REGAINED_RSSI_EVENT_ID ; 
 int SCAN_COMPLETE_EVENT_ID ; 
 int SYNCHRONIZATION_TIMEOUT_EVENT_ID ; 
 scalar_t__ WL1251_ACX_INTR_EVENT_A ; 
 scalar_t__ WL1251_ACX_INTR_EVENT_B ; 
 scalar_t__ WL1251_ACX_INTR_INIT_COMPLETE ; 
 scalar_t__ WL1251_ACX_INTR_RX0_DATA ; 
 scalar_t__ WL1251_ACX_INTR_RX1_DATA ; 
 scalar_t__ WL1251_ACX_INTR_TX_RESULT ; 
 int /*<<< orphan*/  WL1251_PART_WORK_MEM_SIZE ; 
 int /*<<< orphan*/  WL1251_PART_WORK_MEM_START ; 
 int /*<<< orphan*/  WL1251_PART_WORK_REG_SIZE ; 
 int /*<<< orphan*/  WL1251_PART_WORK_REG_START ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_acx_fw_version (struct wl1251*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl1251_boot_set_ecpu_ctrl (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_boot_target_enable_interrupts (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  wl1251_enable_interrupts (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_error (char*) ; 
 int /*<<< orphan*/  wl1251_event_mbox_config (struct wl1251*) ; 
 int wl1251_event_unmask (struct wl1251*) ; 
 void* wl1251_reg_read32 (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_reg_write32 (struct wl1251*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wl1251_set_partition (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wl1251_boot_run_firmware(struct wl1251 *wl)
{
	int loop, ret;
	u32 chip_id, acx_intr;

	wl1251_boot_set_ecpu_ctrl(wl, ECPU_CONTROL_HALT);

	chip_id = wl1251_reg_read32(wl, CHIP_ID_B);

	wl1251_debug(DEBUG_BOOT, "chip id after firmware boot: 0x%x", chip_id);

	if (chip_id != wl->chip_id) {
		wl1251_error("chip id doesn't match after firmware boot");
		return -EIO;
	}

	/* wait for init to complete */
	loop = 0;
	while (loop++ < INIT_LOOP) {
		udelay(INIT_LOOP_DELAY);
		acx_intr = wl1251_reg_read32(wl, ACX_REG_INTERRUPT_NO_CLEAR);

		if (acx_intr == 0xffffffff) {
			wl1251_error("error reading hardware complete "
				     "init indication");
			return -EIO;
		}
		/* check that ACX_INTR_INIT_COMPLETE is enabled */
		else if (acx_intr & WL1251_ACX_INTR_INIT_COMPLETE) {
			wl1251_reg_write32(wl, ACX_REG_INTERRUPT_ACK,
					   WL1251_ACX_INTR_INIT_COMPLETE);
			break;
		}
	}

	if (loop > INIT_LOOP) {
		wl1251_error("timeout waiting for the hardware to "
			     "complete initialization");
		return -EIO;
	}

	/* get hardware config command mail box */
	wl->cmd_box_addr = wl1251_reg_read32(wl, REG_COMMAND_MAILBOX_PTR);

	/* get hardware config event mail box */
	wl->event_box_addr = wl1251_reg_read32(wl, REG_EVENT_MAILBOX_PTR);

	/* set the working partition to its "running" mode offset */
	wl1251_set_partition(wl, WL1251_PART_WORK_MEM_START,
			     WL1251_PART_WORK_MEM_SIZE,
			     WL1251_PART_WORK_REG_START,
			     WL1251_PART_WORK_REG_SIZE);

	wl1251_debug(DEBUG_MAILBOX, "cmd_box_addr 0x%x event_box_addr 0x%x",
		     wl->cmd_box_addr, wl->event_box_addr);

	wl1251_acx_fw_version(wl, wl->fw_ver, sizeof(wl->fw_ver));

	/*
	 * in case of full asynchronous mode the firmware event must be
	 * ready to receive event from the command mailbox
	 */

	/* enable gpio interrupts */
	wl1251_enable_interrupts(wl);

	/* Enable target's interrupts */
	wl->intr_mask = WL1251_ACX_INTR_RX0_DATA |
		WL1251_ACX_INTR_RX1_DATA |
		WL1251_ACX_INTR_TX_RESULT |
		WL1251_ACX_INTR_EVENT_A |
		WL1251_ACX_INTR_EVENT_B |
		WL1251_ACX_INTR_INIT_COMPLETE;
	wl1251_boot_target_enable_interrupts(wl);

	wl->event_mask = SCAN_COMPLETE_EVENT_ID | BSS_LOSE_EVENT_ID |
		SYNCHRONIZATION_TIMEOUT_EVENT_ID |
		ROAMING_TRIGGER_LOW_RSSI_EVENT_ID |
		ROAMING_TRIGGER_REGAINED_RSSI_EVENT_ID |
		REGAINED_BSS_EVENT_ID | BT_PTA_SENSE_EVENT_ID |
		BT_PTA_PREDICTION_EVENT_ID | JOIN_EVENT_COMPLETE_ID;

	ret = wl1251_event_unmask(wl);
	if (ret < 0) {
		wl1251_error("EVENT mask setting failed");
		return ret;
	}

	wl1251_event_mbox_config(wl);

	/* firmware startup completed */
	return 0;
}