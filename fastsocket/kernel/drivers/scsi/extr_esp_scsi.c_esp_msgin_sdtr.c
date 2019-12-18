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
typedef  int u8 ;
struct esp_target_data {int flags; int nego_goal_period; int nego_goal_offset; } ;
struct esp {int* msg_in; int flags; int max_period; int min_period; int ccycle; scalar_t__ rev; int msg_out_len; int /*<<< orphan*/ * msg_out; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  ESP_CMD_SATN ; 
 int ESP_FLAG_DISABLE_SYNC ; 
 int ESP_TGT_NEGO_SYNC ; 
 scalar_t__ FAS236 ; 
 int /*<<< orphan*/  MESSAGE_REJECT ; 
 int /*<<< orphan*/  esp_setsync (struct esp*,struct esp_target_data*,int,int,int,int) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int /*<<< orphan*/ ) ; 
 int spi_populate_sync_msg (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void esp_msgin_sdtr(struct esp *esp, struct esp_target_data *tp)
{
	u8 period = esp->msg_in[3];
	u8 offset = esp->msg_in[4];
	u8 stp;

	if (!(tp->flags & ESP_TGT_NEGO_SYNC))
		goto do_reject;

	if (offset > 15)
		goto do_reject;

	if (esp->flags & ESP_FLAG_DISABLE_SYNC)
		offset = 0;

	if (offset) {
		int one_clock;

		if (period > esp->max_period) {
			period = offset = 0;
			goto do_sdtr;
		}
		if (period < esp->min_period)
			goto do_reject;

		one_clock = esp->ccycle / 1000;
		stp = DIV_ROUND_UP(period << 2, one_clock);
		if (stp && esp->rev >= FAS236) {
			if (stp >= 50)
				stp--;
		}
	} else {
		stp = 0;
	}

	esp_setsync(esp, tp, period, offset, stp, offset);
	return;

do_reject:
	esp->msg_out[0] = MESSAGE_REJECT;
	esp->msg_out_len = 1;
	scsi_esp_cmd(esp, ESP_CMD_SATN);
	return;

do_sdtr:
	tp->nego_goal_period = period;
	tp->nego_goal_offset = offset;
	esp->msg_out_len =
		spi_populate_sync_msg(&esp->msg_out[0],
				      tp->nego_goal_period,
				      tp->nego_goal_offset);
	scsi_esp_cmd(esp, ESP_CMD_SATN);
}