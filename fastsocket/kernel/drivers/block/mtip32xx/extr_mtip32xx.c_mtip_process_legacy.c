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
typedef  int /*<<< orphan*/  u32 ;
struct mtip_port {int /*<<< orphan*/ * cmd_issue; int /*<<< orphan*/  flags; struct mtip_cmd* commands; } ;
struct mtip_cmd {int /*<<< orphan*/  comp_data; int /*<<< orphan*/  (* comp_func ) (struct mtip_port*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct driver_data {struct mtip_port* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTIP_PF_IC_ACTIVE_BIT ; 
 size_t MTIP_TAG_INTERNAL ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mtip_port*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mtip_process_legacy(struct driver_data *dd, u32 port_stat)
{
	struct mtip_port *port = dd->port;
	struct mtip_cmd *cmd = &port->commands[MTIP_TAG_INTERNAL];

	if (test_bit(MTIP_PF_IC_ACTIVE_BIT, &port->flags) &&
	    (cmd != NULL) && !(readl(port->cmd_issue[MTIP_TAG_INTERNAL])
		& (1 << MTIP_TAG_INTERNAL))) {
		if (cmd->comp_func) {
			cmd->comp_func(port,
				MTIP_TAG_INTERNAL,
				cmd->comp_data,
				0);
			return;
		}
	}

	return;
}