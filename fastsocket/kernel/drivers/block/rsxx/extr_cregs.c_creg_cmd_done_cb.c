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
struct rsxx_cardinfo {int dummy; } ;
struct creg_completion {int st; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  creg_status; } ;
struct creg_cmd {int /*<<< orphan*/  status; struct creg_completion* cb_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void creg_cmd_done_cb(struct rsxx_cardinfo *card,
			     struct creg_cmd *cmd,
			     int st)
{
	struct creg_completion *cmd_completion;

	cmd_completion = cmd->cb_private;
	BUG_ON(!cmd_completion);

	cmd_completion->st = st;
	cmd_completion->creg_status = cmd->status;
	complete(cmd_completion->cmd_done);
}