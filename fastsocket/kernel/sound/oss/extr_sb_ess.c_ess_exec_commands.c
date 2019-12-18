#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ess_command {int cmd; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int channels; scalar_t__ bits; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 scalar_t__ AFMT_U8 ; 
 int /*<<< orphan*/  ess_write (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ess_exec_commands
	(sb_devc *devc, struct ess_command *cmdtab[])
{
	struct ess_command *cmd;

	cmd = cmdtab [ ((devc->channels != 1) << 1) + (devc->bits != AFMT_U8) ];

	while (cmd->cmd != -1) {
		ess_write (devc, cmd->cmd, cmd->data);
		cmd++;
	}
}