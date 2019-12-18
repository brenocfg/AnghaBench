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
struct msm_adsp_module {int state; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  ADSP_STATE_DISABLED 130 
#define  ADSP_STATE_ENABLED 129 
#define  ADSP_STATE_ENABLING 128 
 int /*<<< orphan*/  RPC_ADSP_RTOS_CMD_DISABLE ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int rpc_adsp_rtos_app_to_modem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msm_adsp_module*) ; 

__attribute__((used)) static int msm_adsp_disable_locked(struct msm_adsp_module *module)
{
	int rc = 0;

	switch (module->state) {
	case ADSP_STATE_DISABLED:
		pr_warning("adsp: module '%s' already disabled\n",
			   module->name);
		break;
	case ADSP_STATE_ENABLING:
	case ADSP_STATE_ENABLED:
		rc = rpc_adsp_rtos_app_to_modem(RPC_ADSP_RTOS_CMD_DISABLE,
						module->id, module);
		module->state = ADSP_STATE_DISABLED;
	}
	return rc;
}