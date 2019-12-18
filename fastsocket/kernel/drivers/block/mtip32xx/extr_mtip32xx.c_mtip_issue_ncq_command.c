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
struct mtip_port {TYPE_1__* commands; int /*<<< orphan*/  cmd_issue_lock; int /*<<< orphan*/ * cmd_issue; int /*<<< orphan*/ * s_active; } ;
struct TYPE_2__ {scalar_t__ comp_time; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTIP_NCQ_COMMAND_TIMEOUT_MS ; 
 int MTIP_TAG_BIT (int) ; 
 size_t MTIP_TAG_INDEX (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mtip_issue_ncq_command(struct mtip_port *port, int tag)
{
	atomic_set(&port->commands[tag].active, 1);

	spin_lock(&port->cmd_issue_lock);

	writel((1 << MTIP_TAG_BIT(tag)),
			port->s_active[MTIP_TAG_INDEX(tag)]);
	writel((1 << MTIP_TAG_BIT(tag)),
			port->cmd_issue[MTIP_TAG_INDEX(tag)]);

	spin_unlock(&port->cmd_issue_lock);

	/* Set the command's timeout value.*/
	port->commands[tag].comp_time = jiffies + msecs_to_jiffies(
					MTIP_NCQ_COMMAND_TIMEOUT_MS);
}