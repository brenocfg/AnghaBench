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
struct pt_regs {int dummy; } ;
struct mc_request {int /*<<< orphan*/  originating_fd; TYPE_1__* cmd; int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {void (* handler ) (struct mc_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MCONSOLE_IRQ ; 
 int /*<<< orphan*/  deactivate_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mconsole_get_request (int /*<<< orphan*/ ,struct mc_request*) ; 
 void mconsole_go (struct mc_request*) ; 
 int /*<<< orphan*/  mconsole_reply (struct mc_request*,char*,int,int /*<<< orphan*/ ) ; 
 void mconsole_sysrq (struct mc_request*) ; 
 int /*<<< orphan*/  os_set_fd_block (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reactivate_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 void stub1 (struct mc_request*) ; 

void mconsole_stop(struct mc_request *req)
{
	deactivate_fd(req->originating_fd, MCONSOLE_IRQ);
	os_set_fd_block(req->originating_fd, 1);
	mconsole_reply(req, "stopped", 0, 0);
	for (;;) {
		if (!mconsole_get_request(req->originating_fd, req))
			continue;
		if (req->cmd->handler == mconsole_go)
			break;
		if (req->cmd->handler == mconsole_stop) {
			mconsole_reply(req, "Already stopped", 1, 0);
			continue;
		}
		if (req->cmd->handler == mconsole_sysrq) {
			struct pt_regs *old_regs;
			old_regs = set_irq_regs((struct pt_regs *)&req->regs);
			mconsole_sysrq(req);
			set_irq_regs(old_regs);
			continue;
		}
		(*req->cmd->handler)(req);
	}
	os_set_fd_block(req->originating_fd, 0);
	reactivate_fd(req->originating_fd, MCONSOLE_IRQ);
	mconsole_reply(req, "", 0, 0);
}