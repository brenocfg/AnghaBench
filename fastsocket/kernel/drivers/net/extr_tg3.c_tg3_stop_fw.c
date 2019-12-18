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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_APE ; 
 int /*<<< orphan*/  ENABLE_ASF ; 
 int /*<<< orphan*/  FWCMD_NICDRV_PAUSE_FW ; 
 int /*<<< orphan*/  NIC_SRAM_FW_CMD_MBOX ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_generate_fw_event (struct tg3*) ; 
 int /*<<< orphan*/  tg3_wait_for_event_ack (struct tg3*) ; 
 int /*<<< orphan*/  tg3_write_mem (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_stop_fw(struct tg3 *tp)
{
	if (tg3_flag(tp, ENABLE_ASF) && !tg3_flag(tp, ENABLE_APE)) {
		/* Wait for RX cpu to ACK the previous event. */
		tg3_wait_for_event_ack(tp);

		tg3_write_mem(tp, NIC_SRAM_FW_CMD_MBOX, FWCMD_NICDRV_PAUSE_FW);

		tg3_generate_fw_event(tp);

		/* Wait for RX cpu to ACK this event. */
		tg3_wait_for_event_ack(tp);
	}
}