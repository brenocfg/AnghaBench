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
struct msm_adsp_module {scalar_t__ open_count; scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  name; scalar_t__ rpc_client; int /*<<< orphan*/ * driver_data; int /*<<< orphan*/ * ops; scalar_t__ clk; } ;

/* Variables and functions */
 scalar_t__ ADSP_STATE_DISABLED ; 
 int /*<<< orphan*/  INT_ADSP ; 
 int /*<<< orphan*/  adsp_cmd_lock ; 
 scalar_t__ adsp_open_count ; 
 int /*<<< orphan*/  allow_suspend () ; 
 int /*<<< orphan*/  clk_disable (scalar_t__) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_adsp_disable_locked (struct msm_adsp_module*) ; 
 int /*<<< orphan*/  msm_rpc_close (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void msm_adsp_put(struct msm_adsp_module *module)
{
	unsigned long flags;

	mutex_lock(&module->lock);
	if (--module->open_count == 0 && module->clk)
		clk_disable(module->clk);
	if (module->ops) {
		pr_info("adsp: closing module %s\n", module->name);

		/* lock to ensure a dsp event cannot be delivered
		 * during or after removal of the ops and driver_data
		 */
		spin_lock_irqsave(&adsp_cmd_lock, flags);
		module->ops = NULL;
		module->driver_data = NULL;
		spin_unlock_irqrestore(&adsp_cmd_lock, flags);

		if (module->state != ADSP_STATE_DISABLED) {
			pr_info("adsp: disabling module %s\n", module->name);
			msm_adsp_disable_locked(module);
		}

		msm_rpc_close(module->rpc_client);
		module->rpc_client = 0;
		if (--adsp_open_count == 0) {
			disable_irq(INT_ADSP);
			allow_suspend();
			pr_info("adsp: disable interrupt\n");
		}
	} else {
		pr_info("adsp: module %s is already closed\n", module->name);
	}
	mutex_unlock(&module->lock);
}