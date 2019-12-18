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
typedef  int /*<<< orphan*/  u32 ;
struct ipr_ioa_cfg {TYPE_1__* host; } ;
struct ipr_cmnd {int /*<<< orphan*/  completion; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipr_do_req (struct ipr_cmnd*,int /*<<< orphan*/ ,void (*) (struct ipr_cmnd*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_internal_cmd_done ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipr_send_blocking_cmd(struct ipr_cmnd *ipr_cmd,
				  void (*timeout_func) (struct ipr_cmnd *ipr_cmd),
				  u32 timeout)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	init_completion(&ipr_cmd->completion);
	ipr_do_req(ipr_cmd, ipr_internal_cmd_done, timeout_func, timeout);

	spin_unlock_irq(ioa_cfg->host->host_lock);
	wait_for_completion(&ipr_cmd->completion);
	spin_lock_irq(ioa_cfg->host->host_lock);
}