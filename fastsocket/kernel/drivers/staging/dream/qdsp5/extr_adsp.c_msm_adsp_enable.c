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
struct msm_adsp_module {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  name; int /*<<< orphan*/  state_wait; int /*<<< orphan*/  id; } ;

/* Variables and functions */
#define  ADSP_STATE_DISABLED 131 
#define  ADSP_STATE_DISABLING 130 
#define  ADSP_STATE_ENABLED 129 
#define  ADSP_STATE_ENABLING 128 
 int EBUSY ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  RPC_ADSP_RTOS_CMD_ENABLE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int rpc_adsp_rtos_app_to_modem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msm_adsp_module*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

int msm_adsp_enable(struct msm_adsp_module *module)
{
	int rc = 0;

	pr_info("msm_adsp_enable() '%s'state[%d] id[%d]\n",
		module->name, module->state, module->id);

	mutex_lock(&module->lock);
	switch (module->state) {
	case ADSP_STATE_DISABLED:
		rc = rpc_adsp_rtos_app_to_modem(RPC_ADSP_RTOS_CMD_ENABLE,
						module->id, module);
		if (rc)
			break;
		module->state = ADSP_STATE_ENABLING;
		mutex_unlock(&module->lock);
		rc = wait_event_timeout(module->state_wait,
					module->state != ADSP_STATE_ENABLING,
					1 * HZ);
		mutex_lock(&module->lock);
		if (module->state == ADSP_STATE_ENABLED) {
			rc = 0;
		} else {
			pr_err("adsp: module '%s' enable timed out\n",
			       module->name);
			rc = -ETIMEDOUT;
		}
		break;
	case ADSP_STATE_ENABLING:
		pr_warning("adsp: module '%s' enable in progress\n",
			   module->name);
		break;
	case ADSP_STATE_ENABLED:
		pr_warning("adsp: module '%s' already enabled\n",
			   module->name);
		break;
	case ADSP_STATE_DISABLING:
		pr_err("adsp: module '%s' disable in progress\n",
		       module->name);
		rc = -EBUSY;
		break;
	}
	mutex_unlock(&module->lock);
	return rc;
}