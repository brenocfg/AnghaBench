#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_adsp_ops {int dummy; } ;
struct msm_adsp_module {scalar_t__ open_count; int /*<<< orphan*/  lock; scalar_t__ clk; int /*<<< orphan*/  name; int /*<<< orphan*/ * driver_data; struct msm_adsp_ops* ops; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {scalar_t__ init_info_state; int /*<<< orphan*/  init_info_wait; } ;

/* Variables and functions */
 scalar_t__ ADSP_STATE_INIT_INFO ; 
 int EBUSY ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  INT_ADSP ; 
 int /*<<< orphan*/  RPC_ADSP_RTOS_CMD_REGISTER_APP ; 
 TYPE_1__ adsp_info ; 
 scalar_t__ adsp_open_count ; 
 int /*<<< orphan*/  adsp_open_lock ; 
 int adsp_rpc_init (struct msm_adsp_module*) ; 
 int /*<<< orphan*/  allow_suspend () ; 
 int /*<<< orphan*/  clk_disable (scalar_t__) ; 
 int /*<<< orphan*/  clk_enable (scalar_t__) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct msm_adsp_module* find_adsp_module_by_name (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_get_init_info () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  prevent_suspend () ; 
 int rpc_adsp_rtos_app_to_modem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msm_adsp_module*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

int msm_adsp_get(const char *name, struct msm_adsp_module **out,
		 struct msm_adsp_ops *ops, void *driver_data)
{
	struct msm_adsp_module *module;
	int rc = 0;

#if CONFIG_MSM_AMSS_VERSION >= 6350
	static uint32_t init_info_cmd_sent;
	if (!init_info_cmd_sent) {
		msm_get_init_info();
		init_waitqueue_head(&adsp_info.init_info_wait);
		rc = wait_event_timeout(adsp_info.init_info_wait,
			adsp_info.init_info_state == ADSP_STATE_INIT_INFO,
			5 * HZ);
		if (!rc) {
			pr_info("adsp: INIT_INFO failed\n");
			return -ETIMEDOUT;
		}
		init_info_cmd_sent++;
	}
#endif

	module = find_adsp_module_by_name(&adsp_info, name);
	if (!module)
		return -ENODEV;

	mutex_lock(&module->lock);
	pr_info("adsp: opening module %s\n", module->name);
	if (module->open_count++ == 0 && module->clk)
		clk_enable(module->clk);

	mutex_lock(&adsp_open_lock);
	if (adsp_open_count++ == 0) {
		enable_irq(INT_ADSP);
		prevent_suspend();
	}
	mutex_unlock(&adsp_open_lock);

	if (module->ops) {
		rc = -EBUSY;
		goto done;
	}

	rc = adsp_rpc_init(module);
	if (rc)
		goto done;

	module->ops = ops;
	module->driver_data = driver_data;
	*out = module;
	rc = rpc_adsp_rtos_app_to_modem(RPC_ADSP_RTOS_CMD_REGISTER_APP,
					module->id, module);
	if (rc) {
		module->ops = NULL;
		module->driver_data = NULL;
		*out = NULL;
		pr_err("adsp: REGISTER_APP failed\n");
		goto done;
	}

	pr_info("adsp: module %s has been registered\n", module->name);

done:
	mutex_lock(&adsp_open_lock);
	if (rc && --adsp_open_count == 0) {
		disable_irq(INT_ADSP);
		allow_suspend();
	}
	if (rc && --module->open_count == 0 && module->clk)
		clk_disable(module->clk);
	mutex_unlock(&adsp_open_lock);
	mutex_unlock(&module->lock);
	return rc;
}