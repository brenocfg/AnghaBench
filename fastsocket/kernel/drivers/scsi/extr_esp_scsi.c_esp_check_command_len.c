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
struct scsi_cmnd {int cmd_len; } ;
struct esp {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FLAG_DOING_SLOWCMD ; 

__attribute__((used)) static void esp_check_command_len(struct esp *esp, struct scsi_cmnd *cmd)
{
	if (cmd->cmd_len == 6 ||
	    cmd->cmd_len == 10 ||
	    cmd->cmd_len == 12) {
		esp->flags &= ~ESP_FLAG_DOING_SLOWCMD;
	} else {
		esp->flags |= ESP_FLAG_DOING_SLOWCMD;
	}
}