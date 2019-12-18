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
struct se_cmd {int /*<<< orphan*/  se_dev; TYPE_1__* se_tfo; } ;
struct TYPE_2__ {int (* write_pending ) (struct se_cmd*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  pr_debug (char*,struct se_cmd*) ; 
 int stub1 (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_handle_queue_full (struct se_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void transport_write_pending_qf(struct se_cmd *cmd)
{
	int ret;

	ret = cmd->se_tfo->write_pending(cmd);
	if (ret == -EAGAIN || ret == -ENOMEM) {
		pr_debug("Handling write_pending QUEUE__FULL: se_cmd: %p\n",
			 cmd);
		transport_handle_queue_full(cmd, cmd->se_dev);
	}
}