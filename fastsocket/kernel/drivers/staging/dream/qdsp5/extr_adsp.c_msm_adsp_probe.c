#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct platform_device {int dummy; } ;
struct TYPE_6__ {int id; int /*<<< orphan*/  name; } ;
struct msm_adsp_module {size_t id; TYPE_2__ pdev; int /*<<< orphan*/  pmem_regions; int /*<<< orphan*/  patch_event; int /*<<< orphan*/  verify_cmd; int /*<<< orphan*/ * clk; int /*<<< orphan*/  name; TYPE_3__* info; int /*<<< orphan*/  state_wait; int /*<<< orphan*/  lock; } ;
struct adsp_rtos_mp_mtoa_init_info_type {int dummy; } ;
struct TYPE_7__ {unsigned int module_count; int max_module_id; struct msm_adsp_module* init_info_ptr; struct msm_adsp_module** id_to_module; TYPE_1__* module; int /*<<< orphan*/  write_ctrl; int /*<<< orphan*/  read_ctrl; int /*<<< orphan*/  send_irq; } ;
struct TYPE_5__ {size_t id; int /*<<< orphan*/  pdev_name; int /*<<< orphan*/  patch_event; int /*<<< orphan*/  verify_cmd; scalar_t__ clk_rate; scalar_t__ clk_name; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT_ADSP ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ MSM_AD5_BASE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_ADSP_RTOS_MTOA_PROG ; 
 int /*<<< orphan*/  RPC_ADSP_RTOS_MTOA_VERS ; 
 int /*<<< orphan*/  WAKE_LOCK_SUSPEND ; 
 int /*<<< orphan*/  adsp_cmd_lock ; 
 TYPE_3__ adsp_info ; 
 int adsp_init_info (TYPE_3__*) ; 
 int /*<<< orphan*/  adsp_irq_handler ; 
 struct msm_adsp_module* adsp_modules ; 
 int /*<<< orphan*/  adsp_rpc_thread ; 
 int /*<<< orphan*/  adsp_wake_lock ; 
 int /*<<< orphan*/ * clk_get (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct msm_adsp_module*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_adsp_publish_cdevs (struct msm_adsp_module*,unsigned int) ; 
 int /*<<< orphan*/  msm_rpc_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msm_rpc_open () ; 
 int msm_rpc_register_server (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rpc_cb_server_client ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int msm_adsp_probe(struct platform_device *pdev)
{
	unsigned count;
	int rc, i;
	int max_module_id;

	pr_info("adsp: probe\n");

	wake_lock_init(&adsp_wake_lock, WAKE_LOCK_SUSPEND, "adsp");
#if CONFIG_MSM_AMSS_VERSION >= 6350
	adsp_info.init_info_ptr = kzalloc(
		(sizeof(struct adsp_rtos_mp_mtoa_init_info_type)), GFP_KERNEL);
	if (!adsp_info.init_info_ptr)
		return -ENOMEM;
#endif

	rc = adsp_init_info(&adsp_info);
	if (rc)
		return rc;
	adsp_info.send_irq += (uint32_t) MSM_AD5_BASE;
	adsp_info.read_ctrl += (uint32_t) MSM_AD5_BASE;
	adsp_info.write_ctrl += (uint32_t) MSM_AD5_BASE;
	count = adsp_info.module_count;

#if CONFIG_MSM_AMSS_VERSION >= 6350
	max_module_id = count;
#else
	max_module_id = adsp_info.max_module_id + 1;
#endif

	adsp_modules = kzalloc(
		sizeof(struct msm_adsp_module) * count +
		sizeof(void *) * max_module_id, GFP_KERNEL);
	if (!adsp_modules)
		return -ENOMEM;

	adsp_info.id_to_module = (void *) (adsp_modules + count);

	spin_lock_init(&adsp_cmd_lock);

	rc = request_irq(INT_ADSP, adsp_irq_handler, IRQF_TRIGGER_RISING,
			 "adsp", 0);
	if (rc < 0)
		goto fail_request_irq;
	disable_irq(INT_ADSP);

	rpc_cb_server_client = msm_rpc_open();
	if (IS_ERR(rpc_cb_server_client)) {
		rpc_cb_server_client = NULL;
		rc = PTR_ERR(rpc_cb_server_client);
		pr_err("adsp: could not create rpc server (%d)\n", rc);
		goto fail_rpc_open;
	}

	rc = msm_rpc_register_server(rpc_cb_server_client,
				     RPC_ADSP_RTOS_MTOA_PROG,
				     RPC_ADSP_RTOS_MTOA_VERS);
	if (rc) {
		pr_err("adsp: could not register callback server (%d)\n", rc);
		goto fail_rpc_register;
	}

	/* start the kernel thread to process the callbacks */
	kthread_run(adsp_rpc_thread, NULL, "kadspd");

	for (i = 0; i < count; i++) {
		struct msm_adsp_module *mod = adsp_modules + i;
		mutex_init(&mod->lock);
		init_waitqueue_head(&mod->state_wait);
		mod->info = &adsp_info;
		mod->name = adsp_info.module[i].name;
		mod->id = adsp_info.module[i].id;
		if (adsp_info.module[i].clk_name)
			mod->clk = clk_get(NULL, adsp_info.module[i].clk_name);
		else
			mod->clk = NULL;
		if (mod->clk && adsp_info.module[i].clk_rate)
			clk_set_rate(mod->clk, adsp_info.module[i].clk_rate);
		mod->verify_cmd = adsp_info.module[i].verify_cmd;
		mod->patch_event = adsp_info.module[i].patch_event;
		INIT_HLIST_HEAD(&mod->pmem_regions);
		mod->pdev.name = adsp_info.module[i].pdev_name;
		mod->pdev.id = -1;
#if CONFIG_MSM_AMSS_VERSION >= 6350
		adsp_info.id_to_module[i] = mod;
#else
		adsp_info.id_to_module[mod->id] = mod;
#endif
		platform_device_register(&mod->pdev);
	}

	msm_adsp_publish_cdevs(adsp_modules, count);

	return 0;

fail_rpc_register:
	msm_rpc_close(rpc_cb_server_client);
	rpc_cb_server_client = NULL;
fail_rpc_open:
	enable_irq(INT_ADSP);
	free_irq(INT_ADSP, 0);
fail_request_irq:
	kfree(adsp_modules);
#if CONFIG_MSM_AMSS_VERSION >= 6350
	kfree(adsp_info.init_info_ptr);
#endif
	return rc;
}