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
struct task_struct {int dummy; } ;
struct irq_chip {char* name; int /*<<< orphan*/  ack; } ;
struct TYPE_2__ {int /*<<< orphan*/  ack; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  TWL4030_MODULE_INT ; 
 int /*<<< orphan*/  activate_irq (int) ; 
 int /*<<< orphan*/ * create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 struct irq_chip dummy_irq_chip ; 
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * handle_simple_irq ; 
 int /*<<< orphan*/  handle_twl4030_pih ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_event ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,void*,char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,char*,int,unsigned int,int) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_chip_and_handler (int,struct irq_chip*,int /*<<< orphan*/ *) ; 
 int twl4030_init_sih_modules (int /*<<< orphan*/ ) ; 
 unsigned int twl4030_irq_base ; 
 int twl4030_irq_next ; 
 int /*<<< orphan*/  twl4030_irq_thread ; 
 TYPE_1__ twl4030_sih_irq_chip ; 
 int twl4030_sih_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl_irq_line ; 
 int /*<<< orphan*/ * wq ; 

int twl_init_irq(int irq_num, unsigned irq_base, unsigned irq_end)
{
	static struct irq_chip	twl4030_irq_chip;

	int			status;
	int			i;
	struct task_struct	*task;

	/*
	 * Mask and clear all TWL4030 interrupts since initially we do
	 * not have any TWL4030 module interrupt handlers present
	 */
	status = twl4030_init_sih_modules(twl_irq_line);
	if (status < 0)
		return status;

	wq = create_singlethread_workqueue("twl4030-irqchip");
	if (!wq) {
		pr_err("twl4030: workqueue FAIL\n");
		return -ESRCH;
	}

	twl4030_irq_base = irq_base;

	/* install an irq handler for each of the SIH modules;
	 * clone dummy irq_chip since PIH can't *do* anything
	 */
	twl4030_irq_chip = dummy_irq_chip;
	twl4030_irq_chip.name = "twl4030";

	twl4030_sih_irq_chip.ack = dummy_irq_chip.ack;

	for (i = irq_base; i < irq_end; i++) {
		set_irq_chip_and_handler(i, &twl4030_irq_chip,
				handle_simple_irq);
		activate_irq(i);
	}
	twl4030_irq_next = i;
	pr_info("twl4030: %s (irq %d) chaining IRQs %d..%d\n", "PIH",
			irq_num, irq_base, twl4030_irq_next - 1);

	/* ... and the PWR_INT module ... */
	status = twl4030_sih_setup(TWL4030_MODULE_INT);
	if (status < 0) {
		pr_err("twl4030: sih_setup PWR INT --> %d\n", status);
		goto fail;
	}

	/* install an irq handler to demultiplex the TWL4030 interrupt */


	init_completion(&irq_event);

	status = request_irq(irq_num, handle_twl4030_pih, IRQF_DISABLED,
				"TWL4030-PIH", &irq_event);
	if (status < 0) {
		pr_err("twl4030: could not claim irq%d: %d\n", irq_num, status);
		goto fail_rqirq;
	}

	task = kthread_run(twl4030_irq_thread, (void *)irq_num, "twl4030-irq");
	if (IS_ERR(task)) {
		pr_err("twl4030: could not create irq %d thread!\n", irq_num);
		status = PTR_ERR(task);
		goto fail_kthread;
	}
	return status;
fail_kthread:
	free_irq(irq_num, &irq_event);
fail_rqirq:
	/* clean up twl4030_sih_setup */
fail:
	for (i = irq_base; i < irq_end; i++)
		set_irq_chip_and_handler(i, NULL, NULL);
	destroy_workqueue(wq);
	wq = NULL;
	return status;
}