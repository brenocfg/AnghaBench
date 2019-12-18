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
struct scsi_cmnd {TYPE_1__* device; } ;
struct esp_target_data {int flags; scalar_t__ esp_offset; scalar_t__ esp_period; int /*<<< orphan*/  nego_goal_offset; int /*<<< orphan*/  nego_goal_period; } ;
struct esp_cmd_entry {struct scsi_cmnd* cmd; } ;
struct esp {int msg_out_len; int /*<<< orphan*/ * msg_out; struct esp_target_data* target; struct esp_cmd_entry* active_cmd; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_TASK_SET ; 
 int /*<<< orphan*/  ESP_CMD_RATN ; 
 int /*<<< orphan*/  ESP_CMD_SATN ; 
 int ESP_TGT_CHECK_NEGO ; 
 int ESP_TGT_NEGO_SYNC ; 
 int ESP_TGT_NEGO_WIDE ; 
 int ESP_TGT_WIDE ; 
 int /*<<< orphan*/  esp_need_to_nego_sync (struct esp_target_data*) ; 
 int /*<<< orphan*/  esp_setsync (struct esp*,struct esp_target_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int /*<<< orphan*/ ) ; 
 int spi_populate_sync_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_msgin_reject(struct esp *esp)
{
	struct esp_cmd_entry *ent = esp->active_cmd;
	struct scsi_cmnd *cmd = ent->cmd;
	struct esp_target_data *tp;
	int tgt;

	tgt = cmd->device->id;
	tp = &esp->target[tgt];

	if (tp->flags & ESP_TGT_NEGO_WIDE) {
		tp->flags &= ~(ESP_TGT_NEGO_WIDE | ESP_TGT_WIDE);

		if (!esp_need_to_nego_sync(tp)) {
			tp->flags &= ~ESP_TGT_CHECK_NEGO;
			scsi_esp_cmd(esp, ESP_CMD_RATN);
		} else {
			esp->msg_out_len =
				spi_populate_sync_msg(&esp->msg_out[0],
						      tp->nego_goal_period,
						      tp->nego_goal_offset);
			tp->flags |= ESP_TGT_NEGO_SYNC;
			scsi_esp_cmd(esp, ESP_CMD_SATN);
		}
		return;
	}

	if (tp->flags & ESP_TGT_NEGO_SYNC) {
		tp->flags &= ~(ESP_TGT_NEGO_SYNC | ESP_TGT_CHECK_NEGO);
		tp->esp_period = 0;
		tp->esp_offset = 0;
		esp_setsync(esp, tp, 0, 0, 0, 0);
		scsi_esp_cmd(esp, ESP_CMD_RATN);
		return;
	}

	esp->msg_out[0] = ABORT_TASK_SET;
	esp->msg_out_len = 1;
	scsi_esp_cmd(esp, ESP_CMD_SATN);
}